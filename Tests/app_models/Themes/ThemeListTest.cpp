#include <app_models/app_models.h>
#include <gtest/gtest.h>

namespace AppModelsTests {

    class ThemeListTest : public ::testing::Test {
    protected:

        ThemeListTest()
                : themesTree(themeReader.getThemes()),
                  themeList(themesTree),
                  gruvboxTree(themeReader.getThemes().getChildWithProperty(app_models::IDs::name, "Gruvbox")),
                  gruvboxTheme(gruvboxTree)
                  {}

        app_models::ThemeReader themeReader;
        juce::ValueTree themesTree;
        app_models::ThemeList themeList;
        juce::ValueTree gruvboxTree;
        app_models::Theme gruvboxTheme;

    };

    TEST_F(ThemeListTest, isSuitableType)
    {
        EXPECT_EQ(themeList.isSuitableType(gruvboxTree), true) << "A theme value tree was rejected as a suitable type";
        EXPECT_EQ(themeList.isSuitableType(themesTree), false) << "A non-theme value tree was accepted as a suitable type";
    }

    TEST_F(ThemeListTest, createNewObject)
    {

        app_models::Theme* createdTheme = themeList.createNewObject(gruvboxTree);
        EXPECT_EQ(createdTheme->getName(), gruvboxTheme.getName()) << "created theme name is incorrect";
        EXPECT_EQ(createdTheme->getBackgroundColour().toString(), gruvboxTheme.getBackgroundColour().toString()) << "created theme background colour is incorrect";
        EXPECT_EQ(createdTheme->getTextColour().toString(), gruvboxTheme.getTextColour().toString()) << "created theme text colour is incorrect";
        EXPECT_EQ(createdTheme->getColour1().toString(), gruvboxTheme.getColour1().toString()) << "created theme colour 1 is incorrect";
        EXPECT_EQ(createdTheme->getColour2().toString(), gruvboxTheme.getColour2().toString()) << "created theme colour 2 is incorrect";
        EXPECT_EQ(createdTheme->getColour3().toString(), gruvboxTheme.getColour3().toString()) << "created theme colour 3 is incorrect";
        EXPECT_EQ(createdTheme->getColour4().toString(), gruvboxTheme.getColour4().toString()) << "created theme colour 4 is incorrect";
        EXPECT_EQ(createdTheme->getDarkColour1().toString(), gruvboxTheme.getDarkColour1().toString()) << "created theme dark colour 1 is incorrect";
        EXPECT_EQ(createdTheme->getDisabledBackgroundColour().toString(), gruvboxTheme.getDisabledBackgroundColour().toString()) << "created theme disabled background colour is incorrect";
        delete(createdTheme);
    }

}