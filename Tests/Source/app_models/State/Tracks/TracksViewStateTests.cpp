#include <app_models/app_models.h>
#include "UnitTestCategories.h"

namespace AppModelsTests
{
    class TracksViewStateTests : public juce::UnitTest
    {

    public:

        class TracksViewStateListener : public app_models::TracksViewState::Listener
        {

        public:

            int selectedIndex = 0;
            int changeCount = 0;
            void selectedTrackIndexChanged(int newIndex) override {

                changeCount++;
                selectedIndex = newIndex;

            };
        };

        TracksViewStateTests() : juce::UnitTest("TracksViewStateTests class", UnitTestCategories::app_models) {}


        void runTest() override {


            beginTest("someTest");
            {
                expectEquals(1, 1, "failed");
            }


            tracktion_engine::Engine engine {"ENGINE"};

            auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
            app_models::TracksViewState tracksViewState(*edit);

            beginTest("getSelectedPluginIndex");
            {

                // edit is created with 1 audio track, so the selected index should be 0 initially
                expectEquals(tracksViewState.getSelectedTrackIndex(), 0, "initial selected plugin index is incorrect");

            }

            beginTest("setSelectedPluginIndex");
            {

                tracksViewState.setSelectedTrackIndex(2);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 2, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(0);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 0, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(-1);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(-2);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "selected index is not being constrained");

                tracksViewState.setSelectedTrackIndex(-100);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "selected index is not being constrained");

            }

            beginTest("listener");
            {

                TracksViewStateListener l;
                tracksViewState.addListener(&l);
                int initialCount = l.changeCount;
                tracksViewState.setSelectedTrackIndex(5);
                expectEquals(l.changeCount, initialCount + 1, "listener is not responding to changes");
                expectEquals(l.selectedIndex, 5, "newIndex is not correct");

                tracksViewState.removeListener(&l);
                tracksViewState.setSelectedTrackIndex(3);
                expectEquals(l.changeCount, initialCount + 1, "listener is responding to changes after being removed as a listener");

            }

        }

    };

    static TracksViewStateTests tracksViewStateTests;
}

