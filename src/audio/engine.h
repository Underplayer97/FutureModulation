// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 Underplayer97

#pragma once
#include <pipewire/pipewire.h>
#include <pipewire/filter.h>

class engine {
private:
    static void onFilterStateChanged(void* userdata, enum pw_filter_state old, enum pw_filter_state state, const char *error);
    static void onProcess(void* userdata, struct spa_io_position *position);
    static void onStopSignal(void* userdata, int signal);
    void deinitialize();
    pw_main_loop* loop = nullptr;
    pw_filter* filter = nullptr;
    void* input_FL = nullptr;
    void* input_FR = nullptr;
    void* output_FL = nullptr;
    void* output_FR = nullptr;
    bool failed = false;
    bool stopping = false;
    struct spa_source* signalint = nullptr;
    struct spa_source* signalterm = nullptr;
public:
    engine() = default;
    bool run();
    void stop();

    engine(const engine&) = delete;
    engine& operator=(const engine&) = delete;
    engine(engine&&) = delete;
    engine& operator=(engine&&) = delete;
    ~engine();
};
