#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class PresetSlotsTests : public juce::UnitTest
    {

    public:

        class PresetSlotsListener : public app_models::PresetSlots::Listener
        {

        public:

            int changeCount = 0;
            void currentPresetSlotChanged(app_models::PresetSlot *newPresetSlot) override {

                changeCount++;

            };
        };

        PresetSlotsTests() : juce::UnitTest("PresetSlots class", UnitTestCategories::app_models) {}


        void runTest() override {


            juce::ValueTree presetSlotsTree = app_models::StateBuilder::createSynthPresetSlots();
            app_models::PresetSlots presetSlots(presetSlotsTree);
            beginTest("setCurrentPresetSlotNumber");
            {

                presetSlots.setCurrentPresetSlotNumber(5);
                expectEquals(presetSlots.getCurrentPresetSlotNumber(), 5, "current preset slot number was not set");

            }

            beginTest("listener");
            {

                PresetSlotsListener l;
                presetSlots.addListener(&l);
                int initialCount = l.changeCount;
                presetSlots.setCurrentPresetSlotNumber(3);
                expect(l.changeCount == initialCount + 1, "listener is not responding to changes");

                presetSlots.removeListener(&l);
                presetSlots.setCurrentPresetSlotNumber(4);
                expect(l.changeCount == initialCount + 1, "listener is responding to changes after being removed as a listener");

            }

            beginTest("constrainer");
            {

                presetSlots.setCurrentPresetSlotNumber(8);
                presetSlots.setCurrentPresetSlotNumber(9);
                expectEquals(presetSlots.getCurrentPresetSlotNumber(), 8, "upper constraint was ignored");

                presetSlots.setCurrentPresetSlotNumber(1);
                presetSlots.setCurrentPresetSlotNumber(0);
                expectEquals(presetSlots.getCurrentPresetSlotNumber(), 1, "lower constraint was ignored");

                presetSlots.setCurrentPresetSlotNumber(1);
                presetSlots.setCurrentPresetSlotNumber(-1);
                expectEquals(presetSlots.getCurrentPresetSlotNumber(), 1, "lower constraint was ignored");
            }


        }

    };

    static PresetSlotsTests presetSlotsTests;
}

