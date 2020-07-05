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
    Source/Models/StateBuilder.cpp
    Source/Views/LookAndFeel/AppLookAndFeel.cpp
    Source/Views/LookAndFeel/ThemeManager.cpp
    Source/Views/Settings/SettingsView.cpp
    Source/Views/Drum/DrumView.cpp
    Source/Views/Mixer/MixerView.cpp
    Source/Views/Tape/TapeView.cpp
    Source/Views/Synth/SynthView.cpp
    Source/Views/Parameters/Engine/EngineParametersView.cpp
    Source/Views/Parameters/ADSR/ADSRParametersView.cpp
    Source/Views/Parameters/Effect/EffectParametersView.cpp
    Source/Views/Parameters/LFO/LFOParametersView.cpp

)

target_include_directories(LMN PUBLIC
    Source/
    Source/Models
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
    Source/Views/Utilities

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
    juce_analytics
    juce_audio_basics
    juce_audio_devices
    juce_audio_formats
    juce_audio_plugin_client
    juce_audio_processors
    juce_audio_utils
    juce_blocks_basics
    juce_box2d
    juce_core
    juce_cryptography
    juce_data_structures
    juce_dsp
    juce_events
    juce_graphics
    juce_gui_basics
    juce_gui_extra
    juce_opengl
    juce_osc
    juce_product_unlocking
    juce_video
    tracktion_engine
)
