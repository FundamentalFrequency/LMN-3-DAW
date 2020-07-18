#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class PresetSlotTests : public juce::UnitTest
    {

    public:

        PresetSlotTests() : juce::UnitTest("PresetSlot class", UnitTestCategories::app_models) {}


        void runTest() override {

            int number = 1;
            juce::String name = "Preset";
            juce::ValueTree presetTree = app_models::StateBuilder::createPreset(name);
            juce::ValueTree presetSlotTree = app_models::StateBuilder::createPresetSlot(number, presetTree);
            app_models::PresetSlot presetSlot(presetSlotTree);
            beginTest("getNumber");
            {

                expectEquals(presetSlot.getNumber(), number, "incorrect number returned");

            }

        }

    };

    static PresetSlotTests presetSlotTests;
}


