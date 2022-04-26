# LMN-3-DAW
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

This repository houses the code for the LMN-3-DAW. It is a part of the larger LMN-3 project, composed of the following
repositories:
- [LMN-3-DAW](https://github.com/stonepreston/LMN-3-DAW)
- [LMN-3-MCAD](https://github.com/stonepreston/LMN-3-MCAD)
- [LMN-3-ECAD](https://github.com/stonepreston/LMN-3-ECAD)
- [LMN-3-Firmware](https://github.com/stonepreston/LMN-3-Firmware)
- [LMN-3-Emulator](https://github.com/stonepreston/LMN-3-Emulator)

## Dependencies
Some dependencies are necessary to run the software. You can install them all with the following command:
```bash
sudo apt install libasound2-dev libjack-jackd2-dev \
    ladspa-sdk \
    libcurl4-openssl-dev  \
    libfreetype6-dev \
    libx11-dev libxcomposite-dev libxcursor-dev libxcursor-dev libxext-dev libxinerama-dev libxrandr-dev libxrender-dev \
    libwebkit2gtk-4.0-dev \
    libglu1-mesa-dev mesa-common-dev
```

If you wish to build the project from source, you will also need to run the following command to install the build 
dependencies:
```bash
sudo apt install build-essential cmake clang llvm 
```

## Releases
Releases can be found [here](https://github.com/stonepreston/LMN-3-DAW/releases). There are releases for both x86_64 
and ARM architectures. 

## Building From Source

### Cloning the Repository
This repository relies on git submodules. You must clone the submodules as well using:
```bash
git clone --recurse-submodules https://github.com/stonepreston/LMN-3-DAW
```

### Building the Project
CMake is used to build the project. Execute the following commands to build all project targets:
```bash
cmake -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8
```
You will find the corresponding artifacts in the build directory that was created using the commands above. 
`./build/LMN3_artefacts/Release` will contain the main LMN-3 executable. 

## Running the Test Suite
After building the project using the commands above, you can run the test suite by executing the following command:
```bash
./build/Tests/Tests_artefacts/Release/Tests
```

## LMN-3-Emulator
If you lack LMN-3 hardware with which to control the DAW (or just want a more convenient method for testing purposes), 
you can use the [LMN-3-Emulator](https://github.com/stonepreston/LMN-3-Emulator) directly on your desktop. The emulator
sends the very  same MIDI commands as the actual LMN-3 hardware. 

## Contributing
Pull requests are welcome and very much appreciated. Please see [contributing](https://github.com/stonepreston/LMN-3-DAW/blob/master/contributing.md) 
for contribution guidance.

## Demo Video
A demo video showcasing the project can be viewed [here](https://www.youtube.com/watch?v=lYp-KzeMrx0)

## Thanks
This project would not be possible without the following free and open source projects:
- [JUCE](https://github.com/juce-framework/JUCE)
- [Tracktion Engine](https://github.com/Tracktion/tracktion_engine)
- [googletest](https://github.com/google/googletest)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [FontAwesome](https://github.com/FortAwesome/Font-Awesome)
- [CMake](https://gitlab.kitware.com/cmake/cmake)
- [The LLVM Project](https://github.com/llvm/llvm-project)
- [Raspberry Pi](https://github.com/raspberrypi)

and many others. 

