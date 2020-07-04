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

# `juce_generate_juce_header` will create a JuceHeader.h for a given target, which will be generated
# into your build tree. This should be included with `#include <JuceHeader.h>`. The include path for
# this header will be automatically added to the target. The main function of the JuceHeader is to
# include all your JUCE module headers; if you're happy to include module headers directly, you
# probably don't need to call this.
# juce_generate_juce_header(GuiAppExample)

target_sources(LMN PRIVATE
    Source/Main.cpp
    Source/Views/App.cpp
    Source/Models/StateBuilder.cpp

)

target_include_directories(LMN PUBLIC
    Source/
    Source/Models
    Source/Views
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
