cmake_minimum_required(VERSION 3.16)

set(APP_NAME "APP")
project("${APP_NAME}" VERSION 1.0.0)

add_subdirectory(tracktion_engine/modules/juce)
add_subdirectory(Plugins)
add_subdirectory(Tests)

juce_add_gui_app("${APP_NAME}"
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "${APP_NAME}"          # The name of the final executable, which can differ from the target name
)                 

target_sources("${APP_NAME}" PRIVATE
    Source/Main.cpp
    Source/Views/App/App.cpp
    Source/Views/LookAndFeel/AppLookAndFeel.cpp
    Source/Views/Settings/SettingsView.cpp
    Source/Views/Settings/SettingsContentComponent.cpp
    Source/Views/Drum/DrumView.cpp
    Source/Views/Mixer/MixerView.cpp
        Source/Views/Edit/EditView.cpp
    Source/Views/Synth/SynthView.cpp
    Source/Views/Parameters/ParametersView.cpp
    Source/Views/Parameters/Engine/SynthEngineParametersView.cpp
    Source/Views/Parameters/Engine/DrumEngineParametersView.cpp
    Source/Views/Parameters/ADSR/ADSRParametersView.cpp
    Source/Views/Parameters/Effect/EffectParametersView.cpp
    Source/Views/Parameters/LFO/LFOParametersView.cpp
    Source/Views/Parameters/Knobs/KnobsView.cpp
    Source/Views/List/Engine/Synth/SynthEngineListView.cpp
    Source/Views/List/Engine/Synth/SynthEngineListBoxModel.cpp
    Source/Views/List/Engine/Drum/DrumEngineListView.cpp

)

target_include_directories("${APP_NAME}" PUBLIC
    Source/
    Source/Views
    Source/Views/App
    Source/Views/LookAndFeel
    Source/Views/Settings
    Source/Views/Synth
    Source/Views/Drum
    Source/Views/Edit
    Source/Views/Mixer
    Source/Views/Parameters
    Source/Views/Parameters/Engine
    Source/Views/Parameters/ADSR
    Source/Views/Parameters/Effect
    Source/Views/Parameters/LFO
    Source/Views/Parameters/Knobs
    Source/Views/Utilities
    Source/Views/List
    Source/Views/List/Engine
    Source/Views/List/Engine/Synth
    Source/Views/List/Engine/Drum
    Source/ViewModels

)

target_compile_definitions("${APP_NAME}" PRIVATE
    JUCE_PLUGINHOST_VST3=1
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${APP_NAME},JUCE_PROJECT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${APP_NAME},JUCE_VERSION>"
)

# add binary data
juce_add_binary_data(AppData SOURCES
    Source/Views/LookAndFeel/Themes/gruvbox.xml
    Source/Views/LookAndFeel/Themes/nightowl.xml
)

# add tracktion engine as a module
juce_add_module(tracktion_engine/modules/tracktion_engine)
juce_add_module(Source/Modules/app_models)

# link binary data to app models
target_link_libraries(app_models INTERFACE AppData)

target_link_libraries("${APP_NAME}" PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    tracktion_engine
    app_models

)


