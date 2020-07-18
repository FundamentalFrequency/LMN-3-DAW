juce_add_console_app(Tests)

target_sources(Tests PRIVATE
    Source/Main.cpp
    Source/app_models/Utilities/StateBuilderTests.cpp
    Source/app_models/Utilities/ThemeReaderTests.cpp
    Source/app_models/Themes/ThemeListTests.cpp
    Source/app_models/Themes/ThemeTests.cpp
    Source/app_models/Themes/ThemesTests.cpp

    Source/app_models/Parameters/NormalizedParameterTests.cpp
    Source/app_models/Parameters/Engine/EngineParametersTest.cpp
    Source/app_models/Parameters/ADSR/ADSRParametersTests.cpp
    Source/app_models/Parameters/Effect/EffectParametersTests.cpp
    Source/app_models/Parameters/LFO/LFOParametersTests.cpp

    Source/app_models/Presets/PresetTests.cpp
    Source/app_models/Presets/PresetSlotTests.cpp
    Source/app_models/Presets/PresetSlotListTests.cpp
    Source/app_models/Presets/PresetSlotsTests.cpp
)

target_compile_definitions(Tests PRIVATE
    JUCE_UNIT_TESTS=1
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
)

target_link_libraries(Tests PRIVATE
    app_models
)