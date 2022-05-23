cmake_minimum_required(VERSION 3.16)

add_subdirectory("${PROJECT_SOURCE_DIR}/googletest" "googletest")

# keeps cache clean
mark_as_advanced(
        BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
        gmock_build_tests gtest_build_samples gtest_build_tests
        gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

# keeps folders clean
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

juce_add_console_app(Tests)
set_target_properties(Tests PROPERTIES FOLDER Tests)

target_sources(Tests PRIVATE
        Main.cpp
        app_view_models/Edit/ItemList/ListAdapters/TracksListAdapterTest.cpp
        app_view_models/Edit/ItemList/ListAdapters/PluginsListAdapterTest.cpp
        app_view_models/Edit/ItemList/ListAdapters/ModifiersListAdapterTest.cpp
        app_view_models/Edit/ItemList/ItemListStateTest.cpp
        app_view_models/Edit/ItemList/EditItemListViewModelTest.cpp
        app_view_models/Edit/Tracks/TracksListViewModelTest.cpp
        app_view_models/Edit/Tracks/TrackViewModelTest.cpp
        app_view_models/Edit/Plugins/TrackPluginsListViewModelTest.cpp
        app_view_models/Edit/Plugins/AvailablePluginsViewModelTest.cpp
        app_view_models/Edit/Modifiers/TrackModifiersListViewModelTest.cpp
        app_view_models/Edit/Modifiers/AvailableModifiersListViewModelTest.cpp
        app_view_models/Edit/Modifiers/ModifierPluginDestinationsViewModelTest.cpp
        app_view_models/Edit/Modifiers/AvailablePluginParametersListViewModelTest.cpp
        app_view_models/Edit/Tempo/TempoSettingsViewModelTest.cpp
        app_view_models/Edit/Sequencers/StepSequencerViewModelTest.cpp
)

target_compile_definitions(Tests PRIVATE
        JUCE_UNIT_TESTS=0
        JUCE_USE_CURL=0
        JUCE_WEB_BROWSER=0
        JUCE_MODAL_LOOPS_PERMITTED=1
)

target_link_libraries(Tests PRIVATE
        gtest
        gmock
        app_services
        app_models
        app_view_models
        app_configuration
        atomic
        yaml-cpp
)

gtest_discover_tests(Tests
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)

