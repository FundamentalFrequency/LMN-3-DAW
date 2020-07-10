juce_add_console_app(UnitTestRunner)

target_sources(UnitTestRunner PRIVATE
    Source/Main.cpp
)

target_compile_definitions(UnitTestRunner PRIVATE
    JUCE_UNIT_TESTS=1
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
)

target_link_libraries(UnitTestRunner PRIVATE
    app_models
)