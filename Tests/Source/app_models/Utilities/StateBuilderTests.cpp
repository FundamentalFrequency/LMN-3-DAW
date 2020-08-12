#include <app_models/app_models.h>
#include "../../UnitTestCategories.h"
namespace AppModelsTests
{
    class StateBuilderTests : public juce::UnitTest
    {

    public:

        StateBuilderTests() : juce::UnitTest("StateBuilder class", UnitTestCategories::app_models) {}


        void runTest() override {

            beginTest("createTrackPluginsListViewState");
            {

                juce::ValueTree trackPluginsListViewState = app_models::StateBuilder::createTrackPluginsListViewState();

                expect(trackPluginsListViewState.getType() == app_models::IDs::TRACK_PLUGINS_LIST_VIEW_STATE);
                expect(trackPluginsListViewState.hasProperty(app_models::IDs::selectedPluginIndex));
                expect(int(trackPluginsListViewState.getProperty(app_models::IDs::selectedPluginIndex)) == -1);

            }

            beginTest("createInitialStateTree");
            {

                juce::ValueTree state = app_models::StateBuilder::createInitialStateTree();

                expect(state.hasType(app_models::IDs::APP_STATE));
                expect(state.getChildWithName(app_models::IDs::TRACK_PLUGINS_LIST_VIEW_STATE).isValid());
                expect(state.getChildWithName(app_models::IDs::THEMES).isValid());

            }

        }

    };

    static StateBuilderTests stateBuilderTests;
}