#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ThemeTests : public juce::UnitTest
    {

    public:

        ThemeTests() : juce::UnitTest("Theme class", UnitTestCategories::app_models) {}


        void runTest() override {

            app_models::ThemeReader tm;
            juce::ValueTree themesValueTree = tm.getThemes();
            juce::ValueTree gruvboxTree = themesValueTree.getChildWithProperty(app_models::IDs::name, "Gruvbox");

            app_models::Theme gruvboxTheme(gruvboxTree);

            beginTest("getName");
            {

                expectEquals(gruvboxTheme.getName(), gruvboxTree.getProperty(app_models::IDs::name).toString(), "getName() returns incorrect name");

            }

            beginTest("getBackgroundColour");
            {

                expectEquals(gruvboxTheme.getBackgroundColour().toString(), gruvboxTree.getProperty(app_models::IDs::backgroundColour).toString(), "returns incorrect colour");

            }

            beginTest("getTextColour");
            {

                expectEquals(gruvboxTheme.getTextColour().toString(), gruvboxTree.getProperty(app_models::IDs::textColour).toString(), "returns incorrect colour");

            }

            beginTest("getColour1");
            {

                expectEquals(gruvboxTheme.getColour1().toString(), gruvboxTree.getProperty(app_models::IDs::colour1).toString(), "returns incorrect colour");

            }

            beginTest("getColour2");
            {

                expectEquals(gruvboxTheme.getColour2().toString(), gruvboxTree.getProperty(app_models::IDs::colour2).toString(), "returns incorrect colour");

            }

            beginTest("getColour3");
            {

                expectEquals(gruvboxTheme.getColour3().toString(), gruvboxTree.getProperty(app_models::IDs::colour3).toString(), "returns incorrect colour");

            }

            beginTest("getColour4");
            {

                expectEquals(gruvboxTheme.getColour4().toString(), gruvboxTree.getProperty(app_models::IDs::colour4).toString(), "returns incorrect colour");

            }

            beginTest("getDarkColour1");
            {

                expectEquals(gruvboxTheme.getDarColour1().toString(), gruvboxTree.getProperty(app_models::IDs::darkColour1).toString(), "returns incorrect colour");

            }

            beginTest("getDisabledBackgroundColour");
            {

                expectEquals(gruvboxTheme.getDisabledBackgroundColour().toString(), gruvboxTree.getProperty(app_models::IDs::disabledBackgroundColour).toString(), "returns incorrect colour");

            }



        }

    };

    static ThemeTests themeTests;
}
