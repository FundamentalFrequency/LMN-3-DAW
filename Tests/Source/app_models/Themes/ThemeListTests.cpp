#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ThemeListTests : public juce::UnitTest
    {

    public:

        ThemeListTests() : juce::UnitTest("ThemeList class", UnitTestCategories::app_models) {}

        void runTest() override {

            app_models::ThemeReader tm;
            juce::ValueTree themesValueTree = tm.getThemes();
            app_models::ThemeList themeList(themesValueTree);
            juce::ValueTree gruvboxTree = themesValueTree.getChildWithProperty(app_models::IDs::name, "Gruvbox");
            app_models::Theme gruvboxTheme(gruvboxTree);

            beginTest("isSuitableType");
            {

                expect(themeList.isSuitableType(gruvboxTree), "theme value tree was rejected as a suitable type");
                expect(!themeList.isSuitableType(themesValueTree), "non-theme value tree type was considered suitable");

            }

            beginTest("createNewObject");
            {

                app_models::Theme* createdTheme = themeList.createNewObject(gruvboxTree);
                expectEquals(createdTheme->getName(), gruvboxTheme.getName(), "created theme name is incorrect");
                expectEquals(createdTheme->getBackgroundColour().toString(), gruvboxTheme.getBackgroundColour().toString(), "created theme background colour is incorrect");
                expectEquals(createdTheme->getTextColour().toString(), gruvboxTheme.getTextColour().toString(), "created theme text colour is incorrect");
                expectEquals(createdTheme->getColour1().toString(), gruvboxTheme.getColour1().toString(), "created theme colour 1 is incorrect");
                expectEquals(createdTheme->getColour2().toString(), gruvboxTheme.getColour2().toString(), "created theme colour 2 is incorrect");
                expectEquals(createdTheme->getColour3().toString(), gruvboxTheme.getColour3().toString(), "created theme colour 3 is incorrect");
                expectEquals(createdTheme->getColour4().toString(), gruvboxTheme.getColour4().toString(), "created theme colour 4 is incorrect");
                expectEquals(createdTheme->getDarColour1().toString(), gruvboxTheme.getDarColour1().toString(), "created theme dark colour 1 is incorrect");
                expectEquals(createdTheme->getDisabledBackgroundColour().toString(), gruvboxTheme.getDisabledBackgroundColour().toString(), "created theme disabled background colour is incorrect");
                delete(createdTheme);

            }

        }

    };

    static ThemeListTests themeListTests;
}

