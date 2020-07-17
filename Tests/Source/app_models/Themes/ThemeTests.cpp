#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class ThemeTests : public juce::UnitTest
    {

    public:

        ThemeTests() : juce::UnitTest("Theme class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("getName");
            {


                app_models::ThemeReader tm;
                juce::ValueTree themesValueTree = tm.getThemes();
                juce::ValueTree gruvboxTree = themesValueTree.getChildWithProperty(app_models::IDs::name, "Gruvbox");

                app_models::Theme gruvboxTheme(gruvboxTree);
                expectEquals(gruvboxTheme.getName(), juce::String("Gruvbox"), "getName() returns incorrect name");


            }


        }

    };

    static ThemeTests themeTests;
}
