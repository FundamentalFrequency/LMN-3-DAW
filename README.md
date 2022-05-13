# LMN-3-DAW
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

This repository houses the code for the LMN-3-DAW. It is a part of the larger LMN-3 project, composed of the following
repositories:
- [LMN-3-DAW](https://github.com/stonepreston/LMN-3-DAW)
- [LMN-3-MCAD](https://github.com/stonepreston/LMN-3-MCAD)
- [LMN-3-ECAD](https://github.com/stonepreston/LMN-3-ECAD)
- [LMN-3-Firmware](https://github.com/stonepreston/LMN-3-Firmware)
- [LMN-3-Emulator](https://github.com/stonepreston/LMN-3-Emulator)
- [LMN-3-Keycaps](https://github.com/stonepreston/LMN-3-Keycaps)

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

## Releases
Releases can be found [here](https://github.com/stonepreston/LMN-3-DAW/releases). There are releases for both x86_64 
and ARM architectures. 

## Samples
The first time you run the application, the directories `~/.config/LMN-3/synth_samples` and 
`~/.config/LMN-3/drum kits` will be automatically created. See the sections below for details on how to add
synth samples and drum kits to the application.

### Synth Samples
Place any audio sample files you wish to use with the Sampler plugin in `~/.config/LMN-3/synth_samples`. 

### Drum Kits
Drum samples are handled a bit differently than synth samples. Drum kits are essentially directories located in 
`~/.config/LMN-3/drum_kits`, with each kit directory containing a `.yaml` mapping file along with any sample files 
associated with it. 

As an example, suppose I want to make a drum kit called AwesomeDrumKit. I would first create a directory in 
`~/.config/LMN-3/drum_kits` named AwesomeDrumKit.
```
mkdir ~/.config/LMN-3/drum_kits/AwesomeDrumKit
```

I would then add all the samples I want to use in that kit into that 
newly created AwesomeDrumKit folder (if you are doing this using the file browser you will need to make sure
and show hidden folders since `.config` is hidden.) Then I would create the yaml file:
```
touch  ~/.config/LMN-3/drum_kits/AwesomeDrumKit/AwesomeDrumKit.yaml
```
Notice that the `.yaml` file has the same name as its parent directory. You would then edit the file and define the mapping that states which sample is played by which midi note number:
```yaml
name: "AwesomeDrumKit"
mappings:
  - note_number: "53"
    file_name: "cool_sample.wav"
  - note_number: "54"
    file_name: "wacky_sample.wav"
  - note_number: "55"
    file_name: "crazy_sample.wav"
```

This is a manual process. If you want to make
a drum kit, you will need to create the directory to store the kit in, add the audio files to it, and then create the
`.yaml` mapping file. Perhaps someone could make a JUCE application to make this easier (cough...cough).

## Building From Source

### Build Dependencies
If you wish to build the project from source, you will also need to run the following command to install the build
dependencies:
```bash
sudo apt install build-essential cmake clang llvm 
```

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

### Compiling for the Raspberry Pi
If you want to build the DAW for the Raspberry Pi, you will need to either build it on the Pi itself (takes a fair bit of time),
or cross compile it. Cross compilation is outside the scope of this document, but you can take a look at the 
[release workflow](https://github.com/stonepreston/LMN-3-DAW/blob/master/.github/workflows/release.yaml) as well as the
[cross-compiler docker image repository](https://github.com/stonepreston/juce_rpi4_cross_compiler) used to compile
for the Pi4 for insight on how it works. Be thankful for Clang. 

## Running the Test Suite
After building the project using the commands above, you can run the test suite by executing the following command:
```bash
./build/Tests/Tests_artefacts/Release/Tests
```

## LMN-3-Emulator
If you lack LMN-3 hardware with which to control the DAW (or just want a more convenient method for testing purposes), 
you can use the [LMN-3-Emulator](https://github.com/stonepreston/LMN-3-Emulator) directly on your desktop. The emulator
sends the very  same MIDI commands as the actual LMN-3 hardware, though it is missing a few features.

## Contributing
Pull requests are welcome and very much appreciated. Please read the [contributing guide](https://github.com/stonepreston/LMN-3-DAW/blob/master/contributing.md) 
before submitting a pull request.

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

## License
Licensed under the [GPL 3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

This repository also includes the [yaml-cpp](https://github.com/jbeder/yaml-cpp) library which requires the following 
notice be included:

```
Copyright (c) 2008-2015 Jesse Beder.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```