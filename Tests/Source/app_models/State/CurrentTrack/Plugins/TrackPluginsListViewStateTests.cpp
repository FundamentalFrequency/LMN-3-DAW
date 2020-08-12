#include <app_models/app_models.h>
#include "UnitTestCategories.h"
namespace AppModelsTests
{
    class TrackPluginsListViewStateTests : public juce::UnitTest
    {

    public:

        class TrackPluginsListViewStateListener : public app_models::TrackPluginsListViewState::Listener
        {

        public:

            int selectedIndex = 0;
            int changeCount = 0;
            void selectedPluginIndexChanged(int newIndex) override {

                changeCount++;
                selectedIndex = newIndex;

            };
        };

        TrackPluginsListViewStateTests() : juce::UnitTest("TrackPluginsListViewStateTests class", UnitTestCategories::app_models) {}


        void runTest() override {

            juce::ValueTree stateTree = app_models::StateBuilder::createTrackPluginsListViewState();
            app_models::TrackPluginsListViewState tplvs(stateTree);

            beginTest("getSelectedPluginIndex");
            {

                expect(tplvs.getSelectedPluginIndex() == -1, "default selected plugin index is incorrect");

            }

            beginTest("setSelectedPluginIndex");
            {

                tplvs.setSelectedPluginIndex(2);
                expectEquals(tplvs.getSelectedPluginIndex(), 2, "incorrect selected index after being set");

                tplvs.setSelectedPluginIndex(0);
                expectEquals(tplvs.getSelectedPluginIndex(), 0, "incorrect selected index after being set");

                tplvs.setSelectedPluginIndex(-1);
                expectEquals(tplvs.getSelectedPluginIndex(), -1, "incorrect selected index after being set");

                tplvs.setSelectedPluginIndex(-2);
                expectEquals(tplvs.getSelectedPluginIndex(), -1, "selected index is not being constrained");

                tplvs.setSelectedPluginIndex(-100);
                expectEquals(tplvs.getSelectedPluginIndex(), -1, "selected index is not being constrained");

            }

            beginTest("listener");
            {

                TrackPluginsListViewStateListener l;
                tplvs.addListener(&l);
                int initialCount = l.changeCount;
                tplvs.setSelectedPluginIndex(5);
                expectEquals(l.changeCount, initialCount + 1, "listener is not responding to changes");
                expectEquals(l.selectedIndex, 5, "newIndex is not correct");

                tplvs.removeListener(&l);
                tplvs.setSelectedPluginIndex(3);
                expectEquals(l.changeCount, initialCount + 1, "listener is responding to changes after being removed as a listener");

            }

        }

    };

    static TrackPluginsListViewStateTests trackPluginsListViewStateTests;
}

