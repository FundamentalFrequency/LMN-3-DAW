#include <app_models/app_models.h>
#include <gtest/gtest.h>
#include "MockThemeListener.h"
namespace AppModelsTests {

    class ThemesTest : public ::testing::Test {
    protected:

        ThemesTest()
                : themesTree(themeReader.getThemes()),
                  themes(themesTree)
        {}

        app_models::ThemeReader themeReader;
        juce::ValueTree themesTree;
        app_models::Themes themes;

    };

    using ::testing::_;

    TEST_F(ThemesTest, initialThemeName)
    {
        EXPECT_EQ(themes.getCurrentThemeName(), "Gruvbox");
    }

    TEST_F(ThemesTest, setCurrentThemeName)
    {

        themes.setCurrentThemeName("NightOwl");
        EXPECT_EQ(themes.getCurrentThemeName(), "NightOwl");

        themes.setCurrentThemeName("some theme that doesnt exist");
        EXPECT_EQ(themes.getCurrentThemeName(), "NightOwl") << "Theme was changed using non-existant theme name";

    }

    TEST_F(ThemesTest, getThemeNames)
    {
        EXPECT_GT(themes.getThemeNames().size(), 0) << "list of theme names is empty";
    }

    TEST_F(ThemesTest, listener)
    {

        MockThemeListener listener;
        EXPECT_CALL(listener, currentThemeChanged(_))
            .Times(1);

        themes.addListener(&listener);
        themes.setCurrentThemeName("Gruvbox");
        themes.setCurrentThemeName("some theme that doesnt exist");
        themes.removeListener(&listener);
        themes.setCurrentThemeName("Gruvbox");

    }


}