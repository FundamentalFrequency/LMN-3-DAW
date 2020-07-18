#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class PresetTests : public juce::UnitTest
    {

    public:

        PresetTests() : juce::UnitTest("Preset class", UnitTestCategories::app_models) {}


        void runTest() override {

            juce::String name = "Preset";
            juce::ValueTree presetTree = app_models::StateBuilder::createPreset(name);
            app_models::Preset preset(presetTree);
            beginTest("getName");
            {

                expectEquals(preset.getName(), name, "incorrect name returned");

            }

        }

    };

    static PresetTests presetTests;
}

