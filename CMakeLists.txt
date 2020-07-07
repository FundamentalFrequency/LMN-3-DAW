cmake_minimum_required(VERSION 3.16)

project(LMN VERSION 0.0.1)

add_subdirectory(JUCE)  

juce_add_gui_app(LMN
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "LMN"                  # The name of the final executable, which can differ from the target name
)                 

target_sources(LMN PRIVATE
    Source/Main.cpp
    Source/Views/App/App.cpp
    Source/Views/LookAndFeel/AppLookAndFeel.cpp
    Source/Views/Settings/SettingsView.cpp
    Source/Views/Settings/SettingsContentComponent.cpp
    Source/Views/Drum/DrumView.cpp
    Source/Views/Mixer/MixerView.cpp
    Source/Views/Tape/TapeView.cpp
    Source/Views/Synth/SynthView.cpp
    Source/Views/Parameters/Engine/SynthEngineParametersView.cpp
    Source/Views/Parameters/Engine/DrumEngineParametersView.cpp
    Source/Views/Parameters/ADSR/ADSRParametersView.cpp
    Source/Views/Parameters/Effect/EffectParametersView.cpp
    Source/Views/Parameters/LFO/LFOParametersView.cpp
    Source/Views/Parameters/Knobs/KnobsView.cpp
    Source/Views/List/SynthEngineListView.cpp
    Source/Views/List/DrumEngineListView.cpp
    Source/Models/Utilities/StateBuilder.cpp
    Source/Models/Parameters/KnobControlledParameter.cpp
    Source/Models/Parameters/NormalizedParameter.cpp
    Source/Models/Parameters/LFODestinationParameter.cpp
    Source/Models/Parameters/LFOPDestinationParameter.cpp
    Source/Models/Parameters/Engine/EngineParameters.cpp
    Source/Models/Parameters/ADSR/ADSRParameters.cpp
    Source/Models/Parameters/Effect/EffectParameters.cpp
    Source/Models/Parameters/LFO/LFOParameters.cpp
    Source/Models/Presets/Preset.cpp
    Source/Models/Presets/PresetSlot.cpp
    Source/Models/Presets/PresetSlotList.cpp
    Source/Models/Presets/PresetSlots.cpp
    Source/Models/Themes/Theme.cpp
    Source/Models/Themes/ThemeList.cpp
    Source/Models/Themes/Themes.cpp
    Source/Models/Themes/ThemeManager.cpp

)

target_include_directories(LMN PUBLIC
    Source/
    Source/Models
    Source/Models/Utilities
    Source/Models/Parameters
    Source/Models/Parameters/Engine
    Source/Models/Parameters/ADSR
    Source/Models/Parameters/Effect
    Source/Models/Parameters/LFO
    Source/Models/Presets
    Source/Models/Themes
    Source/Views
    Source/Views/App
    Source/Views/LookAndFeel
    Source/Views/Settings
    Source/Views/Synth
    Source/Views/Drum
    Source/Views/Tape
    Source/Views/Mixer
    Source/Views/Parameters
    Source/Views/Parameters/Engine
    Source/Views/Parameters/ADSR
    Source/Views/Parameters/Effect
    Source/Views/Parameters/LFO
    Source/Views/Parameters/Knobs
    Source/Views/Utilities
    Source/Views/List

)

target_compile_definitions(LMN PRIVATE
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:LMN,JUCE_PROJECT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:LMN,JUCE_VERSION>"
)

# add tracktion engine as a module
juce_add_module(tracktion_engine/modules/tracktion_engine)

target_link_libraries(LMN PRIVATE
    juce_audio_basics
    juce_audio_devices
    juce_audio_formats
    juce_audio_processors
    juce_audio_utils
    juce_core
    juce_data_structures
    juce_dsp
    juce_events
    juce_graphics
    juce_gui_basics
    juce_gui_extra
    tracktion_engine
)
