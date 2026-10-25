# Architecture
This document describes the high-level architecture of FutureModulation for developers working with this codebase.

## Overview
FutureModulation is an open-source voice changer for Linux that adds voice filters to OBS, Discord, and other apps through a virtual microphone. 

PipeWire handles audio routing. Qt provides the UI. Effects are data-driven (JSON presets and plugins), and switching between voices is meant to be fast

## Repository Structure
```
FutureModulation/
├── src/
│   ├── audio/                # Microphone routing and mixing handling using PipeWire
│   │    └── engine           # Handles creating and destroying PipeWire filters
│   ├── core/                 # Presets, Effect Chain, DSP, Plugin Hosting
│   └── ui/                   # Front end Graphical User Interface using the Qt Framework
└── docs/
```

## Invariants
- Dependencies point one way: ui → audio → core.
- `core` never includes Qt or PipeWire headers.
- The real-time thread never allocates memory, locks, or does I/O.
- `pw_init` and `pw_deinit` belong to main
- The node currently starts unlinked
