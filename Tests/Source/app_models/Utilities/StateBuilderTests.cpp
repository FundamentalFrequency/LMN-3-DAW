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

                juce::ValueTree state = app_models::StateBuilder::createInitialStateTree();

                expect(state.hasType(app_models::IDs::APP_STATE));
                expect(state.getChildWithName(app_models::IDs::THEMES).isValid());

            }

        }

    };

    static StateBuilderTests stateBuilderTests;
}