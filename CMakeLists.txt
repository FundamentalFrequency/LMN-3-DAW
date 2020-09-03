cmake_minimum_required(VERSION 3.16)

set(APP_NAME "APP")
project("${APP_NAME}" VERSION 1.0.0)

add_subdirectory(tracktion_engine/modules/juce)
add_subdirectory(Plugins)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(Tests)
endif()

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
    Source/Views/LookAndFeel/Labels/LabelColour1LookAndFeel.cpp
    Source/Views/LookAndFeel/ListItems/ListItemColour2LookAndFeel.cpp
    Source/Views/Settings/SettingsView.cpp
    Source/Views/Settings/SettingsContentComponent.cpp
    Source/Views/Utilties/ViewUtilities.cpp
    Source/Views/SimpleList/SimpleListItemView.cpp
    Source/Views/SimpleList/SimpleListModel.cpp
    Source/Views/SimpleList/SimpleListView.cpp
    Source/Views/SimpleList/SplitListView.cpp
    Source/Views/Edit/EditView.cpp
    Source/Views/Edit/CurrentTrack/Plugins/PluginList/TrackPluginsListView.cpp
    Source/Views/Edit/CurrentTrack/Plugins/EmbeddedPluginWindow.h
    Source/Views/Edit/CurrentTrack/Plugins/PluginView.cpp
    Source/Views/Edit/CurrentTrack/Plugins/AvailablePluginsList/AvailablePluginsListView.cpp
    Source/Views/Edit/CurrentTrack/Modifiers/ModifiersList/TrackModifiersListView.cpp
        Source/Views/Edit/CurrentTrack/Modifiers/AvailableModifiersList/AvailableModifiersListView.cpp
    Source/Views/Edit/Tracks/InformationPanelComponent.cpp
    Source/Views/Edit/Tracks/Markers/PlayheadComponent.cpp
    Source/Views/Edit/Tracks/Markers/BeatMarkerComponent.cpp
    Source/Views/Edit/Tracks/TracksView.cpp
    Source/Views/Edit/Tracks/TracksListBoxModel.cpp
    Source/Views/Edit/Tracks/Track/TrackView.cpp
    Source/Views/Edit/Tracks/Track/SelectionShroud.cpp
    Source/Views/Edit/Tracks/Track/Clips/ClipComponent.cpp
    Source/Views/Edit/Tracks/Track/Clips/MidiClipComponent.cpp
    Source/Views/Edit/Tracks/Track/Clips/RecordingClipComponent.cpp

)

target_include_directories("${APP_NAME}" PUBLIC
    Source/
    Source/Views
    Source/Views/App
    Source/Views/LookAndFeel
    Source/Views/LookAndFeel/Labels
    Source/Views/LookAndFeel/ListItems
    Source/Views/Settings
    Source/Views/Utilties
    Source/Views/SimpleList
    Source/Views/Edit
    Source/Views/Edit/CurrentTrack
    Source/Views/Edit/CurrentTrack/Plugins
    Source/Views/Edit/CurrentTrack/Plugins/PluginList
    Source/Views/Edit/CurrentTrack/Plugins/AvailablePluginsList
    Source/Views/Edit/CurrentTrack/Modifiers
    Source/Views/Edit/CurrentTrack/Modifiers/ModifiersList
    Source/Views/Edit/CurrentTrack/Modifiers/AvailableModifiersList
    Source/Views/Edit/Tracks
    Source/Views/Edit/Tracks/Markers
    Source/Views/Edit/Tracks/Track
    Source/Views/Edit/Tracks/Track/Clips
    Source/Views/Utilities

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
    fontawesome/FontAwesome5BrandsRegular400.otf
    fontawesome/FontAwesome5FreeSolid900.otf
    fontawesome/FontAwesome5FreeRegular400.otf
)

# add modules
juce_add_module(tracktion_engine/modules/tracktion_engine)
juce_add_module(fontaudio/wrappers/juce/module/fontaudio)
juce_add_module(Source/Modules/app_navigation)
juce_add_module(Source/Modules/app_services)
juce_add_module(Source/Modules/app_models)
juce_add_module(Source/Modules/app_view_models)

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
    fontaudio
    app_navigation
    app_services
    app_models
    app_view_models
    AppData

)


