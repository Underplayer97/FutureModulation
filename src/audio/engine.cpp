// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 Underplayer97

#include "engine.h"
#include <pipewire/pipewire.h>
#include <pipewire/filter.h>
#include <iostream>
#include <cstring>
#include <csignal>
#include <cstdint>

/**
 *  @brief Runs the PipeWire audio filter.
 *
 *  Prepares PipeWire to create a filter named "FutureModulation".
 *  Registers a real-time callback loop on a dual-channel float input and output port and
 *  connects it to the graph. Returns true if run() operated as intended, if not, returns false.
 *
 */
bool engine::run() {
    failed = false;
    stopping = false;

    loop = pw_main_loop_new(nullptr);

    if (loop == nullptr){
        std::cerr << "Failed to create loop!\n";
        deinitialize();
        failed = true;
        return false;
    }

    signalint = pw_loop_add_signal(pw_main_loop_get_loop(loop), SIGINT, onStopSignal, this);
    signalterm = pw_loop_add_signal(pw_main_loop_get_loop(loop), SIGTERM, onStopSignal, this);

    if (signalint == nullptr || signalterm == nullptr) {
        std::cerr << "Failed to add signals\n";
        deinitialize();
        failed = true;
        return false;
    }

    static constexpr pw_filter_events filter_events = {
        .version = PW_VERSION_FILTER_EVENTS,
        .state_changed = onFilterStateChanged,
        .process = onProcess,
    };

    filter = pw_filter_new_simple(
        pw_main_loop_get_loop(loop),
        "FutureModulation",
        pw_properties_new(
            PW_KEY_MEDIA_TYPE, "Audio",
            PW_KEY_MEDIA_CATEGORY, "Filter",
            PW_KEY_MEDIA_ROLE, "Communication",
            NULL),
            &filter_events,
            this);

    if (filter == nullptr) {
        std::cerr << "Failed to create filter!\n";
        deinitialize();
        failed = true;
        return false;
    }

    input_FL = pw_filter_add_port(
        filter,
        PW_DIRECTION_INPUT,
        PW_FILTER_PORT_FLAG_MAP_BUFFERS,
        0,
        pw_properties_new(
            PW_KEY_FORMAT_DSP, "32 bit float mono audio",
            PW_KEY_PORT_NAME, "input_FL",
            PW_KEY_AUDIO_CHANNEL, "FL",
            NULL),
            nullptr, 0);

    input_FR = pw_filter_add_port(
        filter,
        PW_DIRECTION_INPUT,
        PW_FILTER_PORT_FLAG_MAP_BUFFERS,
        0,
        pw_properties_new(
            PW_KEY_FORMAT_DSP, "32 bit float mono audio",
            PW_KEY_PORT_NAME, "input_FR",
            PW_KEY_AUDIO_CHANNEL, "FR",
            NULL),
            nullptr, 0);

    output_FL = pw_filter_add_port(
        filter,
        PW_DIRECTION_OUTPUT,
        PW_FILTER_PORT_FLAG_MAP_BUFFERS,
        0,
        pw_properties_new(
            PW_KEY_FORMAT_DSP, "32 bit float mono audio",
            PW_KEY_PORT_NAME, "output_FL",
            PW_KEY_AUDIO_CHANNEL, "FL",
            NULL),
            nullptr, 0);

    output_FR = pw_filter_add_port(
        filter,
        PW_DIRECTION_OUTPUT,
        PW_FILTER_PORT_FLAG_MAP_BUFFERS,
        0,
        pw_properties_new(
            PW_KEY_FORMAT_DSP, "32 bit float mono audio",
            PW_KEY_PORT_NAME, "output_FR",
            PW_KEY_AUDIO_CHANNEL, "FR",
            NULL),
            nullptr, 0);

    if (input_FL == nullptr || input_FR == nullptr || output_FL == nullptr || output_FR == nullptr) {
        std::cerr << "Failed to create filter ports!\n";
        deinitialize();
        failed = true;
        return false;
    }

    if (pw_filter_connect(filter,
        PW_FILTER_FLAG_RT_PROCESS,
        nullptr, 0) < 0) {
        std::cerr << "Unable to connect filter!\n";
        deinitialize();
        failed = true;
        return false;
    }

    pw_main_loop_run(loop);
    deinitialize();
    return !failed;
}

void engine::deinitialize() {
    stopping = true;

    if (filter) {
        pw_filter_destroy(filter);
        filter = nullptr;
    }

    input_FL = nullptr;
    input_FR = nullptr;
    output_FL = nullptr;
    output_FR = nullptr;

    if (loop) {
        if (signalint) {
            pw_loop_destroy_source(pw_main_loop_get_loop(loop), signalint);
            signalint = nullptr;
        }

        if (signalterm) {
            pw_loop_destroy_source(pw_main_loop_get_loop(loop), signalterm);
            signalterm = nullptr;
        }

        pw_main_loop_destroy(loop);
        loop = nullptr;
    }
}

void engine::onStopSignal(void* userdata, int) {
    if (!userdata) return;
    auto *self = static_cast<engine*>(userdata);

    self->stop();
}

void engine::stop() {
    stopping = true;

    if (loop)
        pw_main_loop_quit(loop);
}

void engine::onProcess(void *userdata, struct spa_io_position *position) {
    auto *self = static_cast<engine*>(userdata);

    if (position == nullptr)
        return;

    const auto n_samples = static_cast<uint32_t>(position->clock.duration);

    const float *src_L = static_cast<float *>(pw_filter_get_dsp_buffer(self->input_FL, n_samples));
    const float *src_R = static_cast<float *>(pw_filter_get_dsp_buffer(self->input_FR, n_samples));
    auto *dst_L = static_cast<float *>(pw_filter_get_dsp_buffer(self->output_FL, n_samples));
    auto *dst_R = static_cast<float *>(pw_filter_get_dsp_buffer(self->output_FR, n_samples));

    if (dst_L == nullptr) {}
    else if (src_L == nullptr)
        std::memset(dst_L, 0, n_samples * sizeof(float));
    else
        std::memmove(dst_L, src_L, n_samples * sizeof(float));

    if (dst_R == nullptr) {}
    else if (src_R == nullptr)
        std::memset(dst_R, 0, n_samples * sizeof(float));
    else
        std::memmove(dst_R, src_R, n_samples * sizeof(float));
}

void engine::onFilterStateChanged(void* userdata, enum pw_filter_state old, enum pw_filter_state state, const char *error) {
    const bool isError = (state == PW_FILTER_STATE_ERROR);
    const bool disconnected = (old != PW_FILTER_STATE_UNCONNECTED && state == PW_FILTER_STATE_UNCONNECTED);

    if (isError || disconnected) {
        auto* self = static_cast<engine*>(userdata);

        if (error)
            std::cerr << error << "\n";

        if (self->stopping) return;
        std::cerr << "Filter state: " << pw_filter_state_as_string(old) << " -> " << pw_filter_state_as_string(state) << "\n";

        self->failed = true;
        self->stop();
    }
}

engine::~engine() {
    deinitialize();
}