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
            app_view_models::MidiCommandManager midiCommandManager(engine);


            auto editEmpty = tracktion_engine::Edit::createSingleTrackEdit(engine);
            app_view_models::TracksViewModel tracksViewModelEmpty(*editEmpty, midiCommandManager);
            editEmpty->deleteTrack(tracksViewModelEmpty.getSelectedTrack());
            tracksViewModelEmpty.handleUpdateNowIfNeeded();

            beginTest("initial selected plugin index");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);
                // initial value with edit that has at least 1 track should always be 0
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "initial selected plugin index is incorrect for single track edit");

                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "initial selected plugin index is incorrect for edit with 0 tracks");


                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel3(*edit, midiCommandManager);
                expectEquals(tracksViewModel3.getSelectedTrackIndex(), 0, "initial selected plugin index is incorrect for multitrack edit");



            }

            beginTest("setSelectedTrackIndex");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(5);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

                // Edit has 5 tracks
                tracksViewModel.setSelectedTrackIndex(0);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(3);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 3, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(4);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(-1);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "incorrect selected index after being set");

                tracksViewModel.setSelectedTrackIndex(-2);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(-100);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(5);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "selected index is not being constrained");

                tracksViewModel.setSelectedTrackIndex(100);
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 4, "selected index is not being constrained");

                tracksViewModelEmpty.setSelectedTrackIndex(0);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(3);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(4);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(-1);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(-2);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(-100);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(5);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");

                tracksViewModelEmpty.setSelectedTrackIndex(100);
                expectEquals(tracksViewModelEmpty.getSelectedTrackIndex(), -1, "incorrect selected index after being set for empty edit");


            }

            beginTest("getSelectedTrack");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

                tracksViewModel.setSelectedTrackIndex(4);
                expectEquals(tracksViewModel.getSelectedTrack()->getName(), juce::String("Track 5"), "selected track was incorrect");


            }

            beginTest("Selected index changes");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

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
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

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
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

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

            beginTest("selected index behavior with track addition");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

                edit->ensureNumberOfAudioTracks(8);
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "adding tracks changed the selected index");

                // create an empty edit then add a track
                auto edit2 = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_view_models::TracksViewModel tracksViewModel2(*edit2, midiCommandManager);
                edit2->deleteTrack(tracksViewModel2.getSelectedTrack());
                tracksViewModel2.handleUpdateNowIfNeeded();
                edit2->ensureNumberOfAudioTracks(1);
                tracksViewModel2.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel2.getSelectedTrackIndex(), 0, "adding tracks to an empty edit did not set the selected index to 0");


            }
            beginTest("selected index behavior with track deletion");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

                TracksViewModelListener l;
                tracksViewModel.addListener(&l);

                // edit has 1 track initially
                // after deleting the only track the selected index should be -1
                edit->deleteTrack(tracksViewModel.getSelectedTrack());
                tracksViewModel.handleUpdateNowIfNeeded();
                expectEquals(tracksViewModel.getSelectedTrackIndex(), -1, "selected index was not -1 after deleting only track");

                edit->ensureNumberOfAudioTracks(8);
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

            beginTest("Midi commands");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                edit->ensureNumberOfAudioTracks(8);
                app_view_models::TracksViewModel tracksViewModel(*edit, midiCommandManager);

                juce::MidiMessage messageIncrease(juce::MidiMessage::controllerEvent(1, 1, 1));
                midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 1, "selected index did not increase after sending midi controller change message");

                juce::MidiMessage messageDecrease(juce::MidiMessage::controllerEvent(1, 1, 127));
                midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "selected index did not decrease after sending midi controller change message");

                tracksViewModel.setSelectedTrackIndex(7);
                tracksViewModel.handleUpdateNowIfNeeded();
                midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 7, "selected index increased despite being at the last index");

                tracksViewModel.setSelectedTrackIndex(0);
                tracksViewModel.handleUpdateNowIfNeeded();
                midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
                expectEquals(tracksViewModel.getSelectedTrackIndex(), 0, "selected index decreased despite being at the first index");


            }


        }

    };

    static TracksViewModelTests tracksViewModelTests;
}

