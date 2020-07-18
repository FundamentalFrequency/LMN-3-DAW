#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ThemesTests : public juce::UnitTest
    {

    public:

    class ThemesListener : public app_models::Themes::Listener
    {

    public:

        int changeCount = 0;
        void currentThemeChanged(app_models::Theme *newTheme) override {

            changeCount++;

        };
    };

        ThemesTests() : juce::UnitTest("Themes class", UnitTestCategories::app_models) {}

        void runTest() override {

            app_models::ThemeReader tr;
            juce::ValueTree themesTree = tr.getThemes();
            app_models::Themes themes(themesTree);

            beginTest("getCurrentThemeName");
            {

                expectEquals(themes.getCurrentThemeName(), juce::String("Gruvbox"), "default theme is incorrect");

            }

            beginTest("setCurrentThemeName");
            {

                themes.setCurrentThemeName("some theme that does not exist");
                expectEquals(themes.getCurrentThemeName(), juce::String("Gruvbox"), "current theme name gets set for non-existant theme");

                themes.setCurrentThemeName("NightOwl");
                expectEquals(themes.getCurrentThemeName(), juce::String("NightOwl"), "current theme name was not set");

            }

            beginTest("setCurrentThemeName");
            {

                auto themeNamesArray = themes.getThemeNames();

                expect(themeNamesArray.size() > 0,"list of theme names is empty");

            }

            beginTest("listener");
            {

                ThemesListener l;
                themes.addListener(&l);
                int initialCount = l.changeCount;
                themes.setCurrentThemeName("Gruvbox");
                expect(l.changeCount == initialCount + 1, "listener is not responding to changes");

                themes.removeListener(&l);
                themes.setCurrentThemeName("Gruvbox");
                expect(l.changeCount == initialCount + 1, "listener is responding to changes after being removed as a listener");


            }



        }

    };

    static ThemesTests themesTests;
}




