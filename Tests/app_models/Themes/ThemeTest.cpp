#include <app_models/app_models.h>
#include <gtest/gtest.h>

namespace AppModelsTests {

    class ThemeTest : public ::testing::Test {
    protected:

        ThemeTest()
          : gruvboxTree(themeReader.getThemes().getChildWithProperty(app_models::IDs::name, "Gruvbox")),
            gruvboxTheme(gruvboxTree)
        {}

        app_models::ThemeReader themeReader;
        juce::ValueTree gruvboxTree;
        app_models::Theme gruvboxTheme;

    };

    TEST_F(ThemeTest, shouldHaveValidValueTreeState)
    {
        EXPECT_EQ(gruvboxTheme.state.isValid(), true);
    }

    TEST_F(ThemeTest, getName)
    {
        EXPECT_EQ(gruvboxTheme.getName(), juce::String("Gruvbox"));
    }

    TEST_F(ThemeTest, getBackgroundColour)
    {
        EXPECT_EQ(gruvboxTheme.getBackgroundColour().toString(), juce::String("ff1d2021"));
    }

    TEST_F(ThemeTest, getTextColour)
    {
        EXPECT_EQ(gruvboxTheme.getTextColour().toString(), juce::String("ffebdbb2"));
    }

    TEST_F(ThemeTest, getColour1)
    {
        EXPECT_EQ(gruvboxTheme.getColour1().toString(), juce::String("ff458588"));
    }

    TEST_F(ThemeTest, getColour2)
    {
        EXPECT_EQ(gruvboxTheme.getColour2().toString(), juce::String("ff689d6a"));
    }

    TEST_F(ThemeTest, getColour3)
    {
        EXPECT_EQ(gruvboxTheme.getColour3().toString(), juce::String("fffbf1c7"));
    }

    TEST_F(ThemeTest, getColour4)
    {
        EXPECT_EQ(gruvboxTheme.getColour4().toString(), juce::String("ffcc241d"));
    }

    TEST_F(ThemeTest, getDarkColour1)
    {
        EXPECT_EQ(gruvboxTheme.getDarkColour1().toString(), juce::String("ff224244"));
    }

    TEST_F(ThemeTest, getDisabledBackgroundColour)
    {
        EXPECT_EQ(gruvboxTheme.getDisabledBackgroundColour().toString(), juce::String("df282828"));
    }



}