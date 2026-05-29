# ImportExport Workbench

A portable, self-contained workbench for rapid prototyping with the [HOOPS Exchange](https://www.techsoft3d.com/products/hoops/exchange/) SDK.

## Overview

This project is extracted from the HOOPS Exchange SDK sample code **prior to version 2026.3.0** and stripped down to the bare minimum needed for experimentation. It provides a minimal but fully working skeleton to prototype ideas — such as implementing the **Visitor pattern** to traverse a PRC/CAD model tree — without the overhead of a full SDK installation or a larger application framework.

The workbench loads a CAD file via the HOOPS Exchange API (`A3D`), optionally exports it to another format, and offers a clean entry point to insert traversal and processing logic.

## Motivation

When exploring new traversal strategies, design patterns, or data extraction approaches against a HOOPS Exchange model tree, it is useful to have:

- A **minimal, portable** C++ project that compiles out-of-the-box with Visual Studio 2022
- A **stable baseline** — behavior locked to the pre-2026.3.0 SDK surface — so experiments are reproducible regardless of SDK updates
- A **low-friction sandbox** to prototype patterns like Visitor, Iterator, or Observer on top of the `A3DEntity` hierarchy before integrating into a larger codebase

## Repository Contents

| File | Description |
|------|-------------|
| `ImportExport.cpp` | Main entry point — loads a CAD file and exports it; add traversal/prototyping code here |
| `common.hpp` | Utility macros and helpers extracted from the HOOPS Exchange SDK samples (logging, memory tracking, `DataGuard`, etc.) |
| `ImportTraverseExport.sln` | Visual Studio 2022 solution |
| `ImportExport.vcxproj` | VC++ project targeting x64 |
| `HOOPSExchangeSamples.props` | Property sheet for SDK include/lib paths |
| `VS2022.bat` | Convenience script to open the solution in VS 2022 |

## Prerequisites

- **Visual Studio 2022** (v143 toolset, x64)
- **HOOPS Exchange SDK < 2026.3.0** installed and the environment variable `HEXCHANGE_INSTALL_DIR` pointing to its root directory
- A valid `hoops_license.h` (provided with the SDK)

## Getting Started

1. Set the environment variable:
   ```bat
   set HEXCHANGE_INSTALL_DIR=C:\path\to\HoopsExchange
   ```
2. Open the solution:
   ```bat
   VS2022.bat
   ```
3. Build in **Debug** or **Release** (x64).
4. Run with optional arguments:
   ```
   ImportExport.exe [input_file] [output_file] [log_file]
   ```
   If no arguments are given, the default sample CAD file bundled with the SDK is used.

`common.hpp` provides `CHECK_RET` / `TEST_RET` macros and the `DataGuard<T,D>` RAII helper to keep prototype code concise and leak-free.

## License

The source files carry the **Tech Soft 3D** copyright notice and are subject to the terms of your HOOPS Exchange SDK license agreement. This workbench is intended for use by licensed SDK users only.
