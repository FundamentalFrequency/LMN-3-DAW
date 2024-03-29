# Contributing Guide
Please submit pull requests against the main branch. 

## Operating System
The LMN-3-DAW is developed and tested on Linux. It is recommended you use a Debian derivative to stay close 
to the target platform (Raspberry Pi). 

## Code Style
Please format your code before submitting a PR. It will fail the CI linting check otherwise. You can run the following 
command to format it according to the provided .clang-format file:
```bash
sudo apt install clang-format # install clang-format if you don't already have it
find Source/ Tests/ Plugins/ -iname *.h -o -iname *.cpp | xargs clang-format -i --style=file
```

## Unit Tests
If your PR modifies the source/Modules directory, please ensure you also have unit
tests associated with that code. Code in Source/Views is not currently tested. You can run the full test suite using:
```bash
cmake -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release
cmake --build build --target Tests -j8
./build/Tests/Tests_artefacts/Release/Tests
```

All tests must pass for your PR to be merged. 

## Compiler
Clang is used for compilation. This is mainly due to the fact that it is inherently a cross-compiler, so cross-compiling
for the Raspberry Pi is made much easier. 

## Architecture
The project relies (well, attempts to at least) on a model-view-view-model architecture to keep the views loosely-coupled to the internal logic. Try
to keep your views as "simple" as possible. They should really only do two things. Respond to input from the user
(by listening for events from the MIDI command manager object), and display JUCE components. Any actual logic that does 
not have to do with how the application looks belongs in a corresponding view model.

Also note that everything that isn't view code (view-models, models, and others) is in a JUCE module in Source/Modules. 
This allows for this non-view code to be easily tested as JUCE modules are just libraries. These libraries can be linked
with the test executable and the views. The views live in Source/Views, and are not built as a library, but as an actual
executable. 


