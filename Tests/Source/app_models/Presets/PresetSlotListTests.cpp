#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class PresetSlotListTests : public juce::UnitTest
    {

    public:

        PresetSlotListTests() : juce::UnitTest("PresetSlotList class", UnitTestCategories::app_models) {}

        void runTest() override {


            juce::ValueTree presetSlotsValueTree = app_models::StateBuilder::createSynthPresetSlots();
            app_models::PresetSlotList presetSlotList(presetSlotsValueTree);
            juce::ValueTree presetSlotTree = presetSlotsValueTree.getChild(0);
            app_models::PresetSlot presetSlot(presetSlotTree);

            beginTest("isSuitableType");
            {

                expect(presetSlotList.isSuitableType(presetSlotTree), "presetSlot value tree was rejected as a suitable type");
                expect(!presetSlotList.isSuitableType(presetSlotsValueTree), "non-preset value tree type was considered suitable");

            }

            beginTest("createNewObject");
            {

                app_models::PresetSlot* createdPresetSlot = presetSlotList.createNewObject(presetSlotTree);
                expectEquals(createdPresetSlot->getNumber(), presetSlot.getNumber(), "created preset number is incorrect");

                delete(createdPresetSlot);

            }

        }

    };

    static PresetSlotListTests presetSlotListTests;
}

