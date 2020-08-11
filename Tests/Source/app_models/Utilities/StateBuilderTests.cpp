#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class StateBuilderTests : public juce::UnitTest
    {

    public:

        StateBuilderTests() : juce::UnitTest("StateBuilder class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("createInitialStateTree");
            {

                juce::ValueTree state(app_models::IDs::APP_STATE);
                state.addChild(app_models::StateBuilder::createThemes(), -1, nullptr);

                juce::ValueTree state2 = app_models::StateBuilder::createInitialStateTree();
                expect(state.isEquivalentTo(state2), "states do not equal each other");

            }

        }

    };

    static StateBuilderTests stateBuilderTests;
}