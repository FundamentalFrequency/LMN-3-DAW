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

target_sources(Tests PRIVATE
        Main.cpp
        app_models/Utilities/ThemeReaderTest.cpp
        app_models/Utilities/StateBuilderTest.cpp
        app_models/Themes/ThemeTest.cpp
        app_models/Themes/ThemeListTest.cpp
        app_models/Themes/ThemesTest.cpp
        app_view_models/Edit/Tracks/TracksViewModelTest.cpp
        app_view_models/Edit/Tracks/TrackViewModelTest.cpp
        app_view_models/Edit/Plugins/TrackPluginsViewModelTest.cpp
        app_view_models/Edit/Plugins/AvailablePluginsViewModelTest.cpp
)

target_compile_definitions(Tests PRIVATE
        JUCE_UNIT_TESTS=0
        JUCE_USE_CURL=0
        JUCE_WEB_BROWSER=0
)

target_link_libraries(Tests PRIVATE
        gtest
        gmock
        app_services
        app_models
        app_view_models
)

gtest_discover_tests(Tests
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)

set_target_properties(Tests PROPERTIES FOLDER Tests)