#include <app_view_models/app_view_models.h>
#include "UnitTestCategories.h"

namespace AppViewModelsTests
{
    class TracksViewModelTests : public juce::UnitTest
    {

    public:

        class TracksViewModelListener : public app_view_models::TracksViewModel::Listener
        {

        public:

            int selectedIndex = 0;
            int selectedIndexChangeCount = 0;
            void selectedTrackIndexChanged(int newIndex) override {

                selectedIndexChangeCount++;
                selectedIndex = newIndex;

            };

            int tracksChangeCount = 0;
            void tracksChanged() override {

                tracksChangeCount++;

            }

        };


        TracksViewModelTests() : juce::UnitTest("TracksViewModelTests class", UnitTestCategories::app_view_models) {}

        void runTest() override {


            tracktion_engine::Engine engine {"ENGINE"};

            beginTest("getSelectedTrackIndex");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_view_models::TracksViewModel tracksViewModel(*edit);
                // edit is created with 1 audio track, so the selected index should be 0 initially
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "initial selected plugin index is incorrect");

            }

            beginTest("setSelectedTrackIndex");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(5);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                // Edit has 5 tracks
                tracksViewModel.setSelectedTrackIndex(0);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(3);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 3, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(4);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(-1);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), -1, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(-2);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), -1, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(-100);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), -1, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(5);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(100);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "selected index is not being constrained");

            }

            beginTest("getSelectedTrack");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                tracksViewModel.setSelectedTrackIndex(4);
                expectEquals(tracksViewModel.getSelectedTrack()->getName(), juce::String("Track 5"), "selected track was incorrect");


            }

            beginTest("Selected index changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                TracksViewModelListener l;
                tracksViewModel.addListener(&l);

                int initialSelectedIndexChangeCount;
                initialSelectedIndexChangeCount = l.selectedIndexChangeCount;
                tracksViewModel.setSelectedTrackIndex(3);
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.selectedIndexChangeCount, initialSelectedIndexChangeCount + 1, "listener is not responding to selected index changes");
                expectEquals(l.selectedIndex, 3, "newIndex is not correct");

                initialSelectedIndexChangeCount = l.selectedIndexChangeCount;
                tracksViewModel.removeListener(&l);
                tracksViewModel.setSelectedTrackIndex(3);
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.selectedIndexChangeCount, initialSelectedIndexChangeCount, "listener is responding to selected index changes after being removed as a listener");


            }

            beginTest("Track deletion changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                TracksViewModelListener l;
                tracksViewModel.addListener(&l);

                int initialTrackChangeCount;
                initialTrackChangeCount = l.tracksChangeCount;
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.tracksChangeCount, initialTrackChangeCount + 1, "listener is not responding to track deletion changes");

                initialTrackChangeCount = l.tracksChangeCount;
                tracksViewModel.removeListener(&l);
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.tracksChangeCount, initialTrackChangeCount, "listener is responding to track deletion changes after being removed as a listener");

            }

            beginTest("Track addition changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                TracksViewModelListener l;
                tracksViewModel.addListener(&l);

                int initialTrackChangeCount;
                initialTrackChangeCount = l.tracksChangeCount;
                edit->ensureNumberOfAudioTracks(9);
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.tracksChangeCount, initialTrackChangeCount + 1, "listener is not responding to track addition changes");

                initialTrackChangeCount = l.tracksChangeCount;
                tracksViewModel.removeListener(&l);
                edit->ensureNumberOfAudioTracks(10);
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(l.tracksChangeCount, initialTrackChangeCount, "listener is responding to track addition changes after being removed as a listener");

            }

            beginTest("selected index behavior with track deletion");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit);

                TracksViewModelListener l;
                tracksViewModel.addListener(&l);

                tracksViewModel.setSelectedTrackIndex(7);
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 6, "selected index was not decreased after deleting last track");

                tracksViewModel.setSelectedTrackIndex(0);
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "selected index was not 0 after deleting first track");

                tracksViewModel.setSelectedTrackIndex(3);
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 3, "selected index changed after deleting track that was not first or last");

            }


        }

    };

    static TracksViewModelTests tracksViewModelTests;
}

