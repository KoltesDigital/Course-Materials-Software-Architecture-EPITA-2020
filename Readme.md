# Game Architecture - EPITA 2020

> Course materials. Contains voluntary errors and design flaws which are addressed during the courses :)

## Requirements

Although the code should support multiple platforms, only precompiled libraries for Windows are given.

1. [Visual Studio 2017 or 2019](https://www.visualstudio.com/downloads/)
2. [Premake 5](https://premake.github.io/download.html)

## Build

Open a terminal in _StealthFactor_ directory and follow the instructions for your platform.

### Windows

    premake5.exe vs2019

Open _build\StealthFactor.sln_, choose your target, and build.

### Linux

    premake5 gmake
    cd build
    make config=release_linux64

## External dependencies

1. [cli.cpp](https://github.com/KoltesDigital/cli.cpp), a CLI argument parser (header-only)
2. [ODE](http://www.ode.org/), a physics engine
3. [pugixml](http://pugixml.org/), an XML parser (header-only)
4. [SFML](https://www.sfml-dev.org/), a small multimedia framework
