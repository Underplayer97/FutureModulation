// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 Underplayer97

#include "audio/engine.h"
#include <pipewire/pipewire.h>
#include <cstdlib>

int main() {
    pw_init(nullptr, nullptr);
    bool pw_status = true;

    {
        engine pw_engine;
        pw_status = pw_engine.run();
    }

    pw_deinit();
    return pw_status ? EXIT_SUCCESS : EXIT_FAILURE;
}
