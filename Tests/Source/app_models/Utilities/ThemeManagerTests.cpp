#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ThemeManagerTests : public juce::UnitTest
    {

    public:

        ThemeManagerTests() : juce::UnitTest("ThemeManager class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("getThemes");
            {

                app_models::ThemeManager tm;
                juce::ValueTree themes = tm.getThemes();

                expectEquals(themes.getType(), app_models::IDs::THEMES, "themes has incorrect identifier");
                expectEquals(themes.getProperty(app_models::IDs::currentTheme).toString(), juce::String("Gruvbox"), "default current theme is incorrect");

                juce::ValueTree theme = themes.getChild(0);
                expectEquals(theme.getType(), app_models::IDs::THEME, "theme has incorrect type");
                expect(theme.hasProperty(app_models::IDs::name), "theme is missing name property");
                expect(theme.hasProperty(app_models::IDs::backgroundColour), "theme is missing backgroundColour property");
                expect(theme.hasProperty(app_models::IDs::textColour), "theme is missing textColour property");
                expect(theme.hasProperty(app_models::IDs::colour1), "theme is missing colour1 property");
                expect(theme.hasProperty(app_models::IDs::colour2), "theme is missing colour2 property");
                expect(theme.hasProperty(app_models::IDs::colour3), "theme is missing colour3 property");
                expect(theme.hasProperty(app_models::IDs::colour4), "theme is missing colour4 property");
                expect(theme.hasProperty(app_models::IDs::darkColour1), "theme is missing darkColour1 property");
                expect(theme.hasProperty(app_models::IDs::disabledBackgroundColour), "theme is missing disabledBackgroundColour property");


            }


        }

    };

    static ThemeManagerTests themeManagerTests;
}
