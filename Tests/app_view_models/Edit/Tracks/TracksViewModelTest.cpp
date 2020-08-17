#include <app_models/app_models.h>
#include <gtest/gtest.h>
#include "MockTracksViewModelListener.h"

namespace AppViewModelsTests {

    class TracksViewModelTest : public ::testing::Test {
    protected:

        TracksViewModelTest()
                : midiCommandManager(engine),
                  selectionManager(engine),
                  singleTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  zeroTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singleTrackViewModel(*singleTrackEdit, midiCommandManager, selectionManager),
                  multiTrackViewModel(*multiTrackEdit, midiCommandManager, selectionManager),
                  zeroTrackViewModel(*zeroTrackEdit, midiCommandManager, selectionManager)

        {}

        void SetUp() override
        {

            multiTrackEdit->ensureNumberOfAudioTracks(8);
            multiTrackViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after a track gets added
            zeroTrackViewModel.handleUpdateNowIfNeeded();

            zeroTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*zeroTrackEdit).getUnchecked(0));
            zeroTrackViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after a track gets added
            zeroTrackViewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine {"ENGINE"};
        app_view_models::MidiCommandManager midiCommandManager;
        tracktion_engine::SelectionManager selectionManager;
        std::unique_ptr<tracktion_engine::Edit> singleTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> multiTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> zeroTrackEdit;
        app_view_models::TracksViewModel singleTrackViewModel;
        app_view_models::TracksViewModel multiTrackViewModel;
        app_view_models::TracksViewModel zeroTrackViewModel;
        juce::MidiMessage messageIncrease = juce::MidiMessage::controllerEvent(1, 1, 1);
        juce::MidiMessage messageDecrease = juce::MidiMessage::controllerEvent(1, 1, 127);

    };



    TEST_F(TracksViewModelTest, initialSelectedTrackIndex)
    {

        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0) << "incorrect initial track index for single track edit";
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0) << "incorrect initial track index for multi-track edit";
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1) << "incorrect initial track index for zero-track edit";

    }

    TEST_F(TracksViewModelTest, setSelectedTrackIndexSingleTrack)
    {

        // Single Track
        singleTrackViewModel.setSelectedTrackIndex(-1);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(-2);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(-100);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(0);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(1);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(2);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);
        singleTrackViewModel.setSelectedTrackIndex(100);
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);

    }


    TEST_F(TracksViewModelTest, setSelectedTrackIndexMultiTrack)
    {
        // Multi-Track
        multiTrackViewModel.setSelectedTrackIndex(7);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 7);
        multiTrackViewModel.setSelectedTrackIndex(-1);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);
        multiTrackViewModel.setSelectedTrackIndex(-2);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);
        multiTrackViewModel.setSelectedTrackIndex(-100);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);
        multiTrackViewModel.setSelectedTrackIndex(0);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);
        multiTrackViewModel.setSelectedTrackIndex(7);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 7);
        multiTrackViewModel.setSelectedTrackIndex(8);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 7);
        multiTrackViewModel.setSelectedTrackIndex(100);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 7);

    }

    TEST_F(TracksViewModelTest, setSelectedTrackIndexZeroTrack)
    {
        // Multi-Track
        zeroTrackViewModel.setSelectedTrackIndex(-1);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(-2);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(-100);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(0);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(7);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(8);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);
        zeroTrackViewModel.setSelectedTrackIndex(100);
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);

    }

    TEST_F(TracksViewModelTest, getSelectedTrackSingleTrack)
    {

        EXPECT_EQ(singleTrackViewModel.getSelectedTrack()->getName(), juce::String("Track 1"));

    }

    TEST_F(TracksViewModelTest, getSelectedTrackMultiTrack)
    {

        multiTrackViewModel.setSelectedTrackIndex(7);
        EXPECT_EQ(multiTrackViewModel.getSelectedTrack()->getName(), juce::String("Track 8"));

    }

    TEST_F(TracksViewModelTest, getSelectedTrackZeroTrack)
    {

        EXPECT_EQ(zeroTrackViewModel.getSelectedTrack(), nullptr);

    }

    using ::testing::_;
    TEST_F(TracksViewModelTest, selectedIndexChangesSingleTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, selectedTrackIndexChanged(0))
                .Times(1);

        singleTrackViewModel.addListener(&listener);

        singleTrackViewModel.setSelectedTrackIndex(-10);
        singleTrackViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.setSelectedTrackIndex(-1);
        singleTrackViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.setSelectedTrackIndex(-100);
        singleTrackViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.setSelectedTrackIndex(1);
        singleTrackViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.setSelectedTrackIndex(100);
        singleTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, selectedIndexChangesMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, selectedTrackIndexChanged(3))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(7))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(0))
                .Times(1);

        multiTrackViewModel.addListener(&listener);

        multiTrackViewModel.setSelectedTrackIndex(3);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.setSelectedTrackIndex(10);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.setSelectedTrackIndex(12);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.setSelectedTrackIndex(-1);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.setSelectedTrackIndex(-10);
        multiTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, selectedIndexChangesZeroTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        zeroTrackViewModel.addListener(&listener);

        zeroTrackViewModel.setSelectedTrackIndex(3);
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        zeroTrackViewModel.setSelectedTrackIndex(10);
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        zeroTrackViewModel.setSelectedTrackIndex(12);
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        zeroTrackViewModel.setSelectedTrackIndex(-1);
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        zeroTrackViewModel.setSelectedTrackIndex(-10);
        zeroTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, trackDeletionChangesSingleTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(-1))
                .Times(1);

        singleTrackViewModel.addListener(&listener);
        singleTrackEdit->deleteTrack(singleTrackViewModel.getSelectedTrack());
        singleTrackViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        singleTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, lastTrackDeletionChangesMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(6))
                .Times(1);

        multiTrackViewModel.setSelectedTrackIndex(7);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(7));
        multiTrackViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, nonEdgeTrackDeletionChangesMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        multiTrackViewModel.setSelectedTrackIndex(3);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(3));
        multiTrackViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, firstTrackDeletionChangesMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        multiTrackViewModel.setSelectedTrackIndex(0);
        multiTrackViewModel.handleUpdateNowIfNeeded();

        multiTrackViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(0));
        multiTrackViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksViewModelTest, trackAdditionChangesZeroTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(0))
                .Times(1);

        zeroTrackViewModel.addListener(&listener);
        zeroTrackEdit->ensureNumberOfAudioTracks(1);
        zeroTrackViewModel.handleUpdateNowIfNeeded();
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), 0);

    }

    TEST_F(TracksViewModelTest, trackAdditionChangesSingleTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        singleTrackViewModel.addListener(&listener);
        singleTrackEdit->ensureNumberOfAudioTracks(4);
        singleTrackViewModel.handleUpdateNowIfNeeded();
        singleTrackViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);

    }

    TEST_F(TracksViewModelTest, trackAdditionChangesMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, tracksChanged())
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        multiTrackViewModel.addListener(&listener);
        multiTrackEdit->ensureNumberOfAudioTracks(16);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        multiTrackViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);

    }


    TEST_F(TracksViewModelTest, midiCommandsSingleTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        singleTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        singleTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);

    }

    TEST_F(TracksViewModelTest, midiCommandsIncreaseMultiTrack)
    {

        MockTracksViewModelListener listener;
        EXPECT_CALL(listener, selectedTrackIndexChanged(1))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(7))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(2))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(3))
                .Times(1);

        multiTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 1);

        multiTrackViewModel.setSelectedTrackIndex(7);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 7);

        multiTrackViewModel.setSelectedTrackIndex(2);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 3);

    }

    TEST_F(TracksViewModelTest, midiCommandsDecreaseMultiTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(2))
                .Times(1);

        EXPECT_CALL(listener, selectedTrackIndexChanged(1))
                .Times(1);

        multiTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 0);

        multiTrackViewModel.setSelectedTrackIndex(2);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.getSelectedTrackIndex(), 1);

    }

    TEST_F(TracksViewModelTest, midiCommandsIncreaseSingleTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        singleTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        singleTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);


    }

    TEST_F(TracksViewModelTest, midiCommandsDecreaseSingleTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        singleTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
        singleTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackViewModel.getSelectedTrackIndex(), 0);

    }

    TEST_F(TracksViewModelTest, midiCommandsIncreaseZeroTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        zeroTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageIncrease, "TEST");
        zeroTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);


    }

    TEST_F(TracksViewModelTest, midiCommandsDecreaseZeroTrack)
    {

        MockTracksViewModelListener listener;

        EXPECT_CALL(listener, selectedTrackIndexChanged(_))
                .Times(0);

        zeroTrackViewModel.addListener(&listener);
        midiCommandManager.midiMessageReceived(messageDecrease, "TEST");
        zeroTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(zeroTrackViewModel.getSelectedTrackIndex(), -1);


    }

    TEST_F(TracksViewModelTest, selection)
    {

        multiTrackViewModel.setSelectedTrackIndex(7);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(selectionManager.isSelected(multiTrackViewModel.getSelectedTrack()), true);

        auto previouslySelectedTrack = multiTrackViewModel.getSelectedTrack();
        multiTrackViewModel.setSelectedTrackIndex(3);
        multiTrackViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(selectionManager.isSelected(previouslySelectedTrack), false);

    }



}