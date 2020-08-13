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
            int selectedIndexChangeCount = 0;
            void selectedTrackIndexChanged(int newIndex) override {

                selectedIndexChangeCount++;
                selectedIndex = newIndex;

            };

            int tracksDeletedCount = 0;
            void trackDeleted() override {

                tracksDeletedCount++;

            }
        };

        TracksViewStateTests() : juce::UnitTest("TracksViewStateTests class", UnitTestCategories::app_models) {}


        void runTest() override {


            tracktion_engine::Engine engine {"ENGINE"};

            beginTest("getSelectedPluginIndex");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_models::TracksViewState tracksViewState(*edit);
                // edit is created with 1 audio track, so the selected index should be 0 initially
                expectEquals(tracksViewState.getSelectedTrackIndex(), 0, "initial selected plugin index is incorrect");

            }

            beginTest("setSelectedPluginIndex");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(5);
                app_models::TracksViewState tracksViewState(*edit);

                // Edit has 5 tracks
                tracksViewState.setSelectedTrackIndex(0);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 0, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(3);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 3, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(4);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 4, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(-1);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "incorrect selected index after being set");

                tracksViewState.setSelectedTrackIndex(-2);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "selected index is not being constrained");

                tracksViewState.setSelectedTrackIndex(-100);
                expectEquals(tracksViewState.getSelectedTrackIndex(), -1, "selected index is not being constrained");

                tracksViewState.setSelectedTrackIndex(5);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 4, "selected index is not being constrained");

                tracksViewState.setSelectedTrackIndex(100);
                expectEquals(tracksViewState.getSelectedTrackIndex(), 4, "selected index is not being constrained");

            }

            beginTest("Selected Index Changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_models::TracksViewState tracksViewState(*edit);

                TracksViewStateListener l;
                tracksViewState.addListener(&l);

                int initialSelectedIndexChangeCount;
                initialSelectedIndexChangeCount = l.selectedIndexChangeCount;
                tracksViewState.setSelectedTrackIndex(3);
                expectEquals(l.selectedIndexChangeCount, initialSelectedIndexChangeCount + 1, "listener is not responding to selected index changes");
                expectEquals(l.selectedIndex, 3, "newIndex is not correct");

                initialSelectedIndexChangeCount = l.selectedIndexChangeCount;
                tracksViewState.removeListener(&l);
                tracksViewState.setSelectedTrackIndex(3);
                expectEquals(l.selectedIndexChangeCount, initialSelectedIndexChangeCount, "listener is responding to selected index changes after being removed as a listener");


            }

            beginTest("Track deletion changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_models::TracksViewState tracksViewState(*edit);

                TracksViewStateListener l;
                tracksViewState.addListener(&l);

                int initialTrackChangeCount;
                initialTrackChangeCount = l.tracksDeletedCount;
                edit->deleteTrack(tracksViewState.getSelectedTrack());
                expectEquals(l.tracksDeletedCount, initialTrackChangeCount + 1, "listener is not responding to track deletion changes");

                initialTrackChangeCount = l.tracksDeletedCount;
                tracksViewState.removeListener(&l);
                edit->deleteTrack(tracksViewState.getSelectedTrack());
                expectEquals(l.tracksDeletedCount, initialTrackChangeCount, "listener is responding to track deletion changes after being removed as a listener");

            }

            beginTest("track deletion");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_models::TracksViewState tracksViewState(*edit);

                TracksViewStateListener l;
                tracksViewState.addListener(&l);

                tracksViewState.setSelectedTrackIndex(7);
                edit->deleteTrack(tracksViewState.getSelectedTrack());
                expectEquals(tracksViewState.getSelectedTrackIndex(), 6, "selected index was not decreased after deleting last track");

                tracksViewState.setSelectedTrackIndex(0);
                edit->deleteTrack(tracksViewState.getSelectedTrack());
                expectEquals(tracksViewState.getSelectedTrackIndex(), 0, "selected index was not 0 after deleting first track");

                tracksViewState.setSelectedTrackIndex(3);
                edit->deleteTrack(tracksViewState.getSelectedTrack());
                expectEquals(tracksViewState.getSelectedTrackIndex(), 3, "selected index changed after deleting track that was not first or last");


            }

        }

    };

    static TracksViewStateTests tracksViewStateTests;
}

