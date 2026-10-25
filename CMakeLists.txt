# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 Underplayer97

cmake_minimum_required(VERSION 3.25)
project(FutureModulation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

include(FetchContent)
FetchContent_Declare(nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        FIND_PACKAGE_ARGS 3.11)
FetchContent_MakeAvailable(nlohmann_json)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PipeWire REQUIRED IMPORTED_TARGET libpipewire-0.3)

qt_add_executable(FutureModulation src/main.cpp
        src/audio/engine.cpp
        src/audio/engine.h)

# TODO: Setup option to have -fsanitize=address... enabled if wanted
target_compile_features(FutureModulation PRIVATE cxx_std_23)
target_compile_options(FutureModulation PRIVATE -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer -g)
target_link_options(FutureModulation PRIVATE -fsanitize=address)

target_link_libraries(FutureModulation PRIVATE
        Qt6::Widgets
        nlohmann_json::nlohmann_json
        PkgConfig::PipeWire)