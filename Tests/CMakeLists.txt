juce_add_console_app(Tests)

target_sources(Tests PRIVATE
    Source/Main.cpp
    Source/app_models/Utilities/StateBuilderTests.cpp
    Source/app_models/Utilities/ThemeReaderTests.cpp
    Source/app_models/Themes/ThemeListTests.cpp
    Source/app_models/Themes/ThemeTests.cpp
    Source/app_models/Themes/ThemesTests.cpp

    Source/app_models/Parameters/NormalizedParameterTests.cpp

)

target_compile_definitions(Tests PRIVATE
    JUCE_UNIT_TESTS=1
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
)

target_link_libraries(Tests PRIVATE
    app_models
)