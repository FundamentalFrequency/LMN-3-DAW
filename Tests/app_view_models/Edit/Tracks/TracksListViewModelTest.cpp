#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockTracksListViewModelListener.h"
#include "../EditItemList/MockEditItemListViewModelListener.h"

namespace AppViewModelsTests {

    class TracksListViewModelTest : public ::testing::Test {
    protected:

        TracksListViewModelTest()
                : singleTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  zeroTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singleTrackSelectionManager(engine),
                  multiTrackSelectionManager(engine),
                  zeroTrackSelectionManager(engine),
                  singleTrackCamera(7.0),
                  multiTrackCamera(7.0),
                  zeroTrackCamera(7.0),
                  singleTrackViewModel(*singleTrackEdit, singleTrackSelectionManager, singleTrackCamera),
                  multiTrackViewModel(*multiTrackEdit, multiTrackSelectionManager, multiTrackCamera),
                  zeroTrackViewModel(*zeroTrackEdit, zeroTrackSelectionManager, zeroTrackCamera)
                  {}

        void SetUp() override {

            singleTrackViewModel.handleUpdateNowIfNeeded();
            multiTrackViewModel.handleUpdateNowIfNeeded();
            zeroTrackViewModel.handleUpdateNowIfNeeded();

            singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
            multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
            zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();

            multiTrackEdit->ensureNumberOfAudioTracks(8);
            multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after an item gets added
            multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();

            zeroTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*zeroTrackEdit)[0]);
            zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after an item gets added
            zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager singleTrackSelectionManager;
        tracktion_engine::SelectionManager multiTrackSelectionManager;
        tracktion_engine::SelectionManager zeroTrackSelectionManager;
        std::unique_ptr<tracktion_engine::Edit> singleTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> multiTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> zeroTrackEdit;
        app_services::TimelineCamera singleTrackCamera;
        app_services::TimelineCamera multiTrackCamera;
        app_services::TimelineCamera zeroTrackCamera;
        app_view_models::TracksListViewModel singleTrackViewModel;
        app_view_models::TracksListViewModel multiTrackViewModel;
        app_view_models::TracksListViewModel zeroTrackViewModel;


    };

    using ::testing::_;
    TEST_F(TracksListViewModelTest, deleteSelectedTrackZeroTrack)
    {

        MockEditItemListViewModelListener listListener;

        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(1);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(-1))
                .Times(1);

        zeroTrackViewModel.listViewModel.addListener(&listListener);
        zeroTrackViewModel.deleteSelectedTrack();
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(zeroTrackViewModel.listViewModel.getAdapter()->size(), 0);

    }

    TEST_F(TracksListViewModelTest, deleteSelectedTrackSingleTrack)
    {

        // Cannot delete the only remaining track

        MockEditItemListViewModelListener listListener;

        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(1);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(0))
                .Times(1);

        singleTrackViewModel.listViewModel.addListener(&listListener);
        singleTrackViewModel.deleteSelectedTrack();
        singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackViewModel.listViewModel.getAdapter()->size(), 1);

        EXPECT_EQ(singleTrackSelectionManager.isSelected(
                dynamic_cast<const tracktion_engine::Selectable *>(singleTrackViewModel.listViewModel.getAdapter()->getItemAtIndex(0))), true);

    }

    TEST_F(TracksListViewModelTest, deleteSelectedTrackMultiTrack)
    {

        MockEditItemListViewModelListener listListener;

        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(0))
                .Times(1);


        multiTrackViewModel.listViewModel.addListener(&listListener);
        multiTrackViewModel.deleteSelectedTrack();
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.listViewModel.getAdapter()->size(), 7);
        EXPECT_EQ(multiTrackSelectionManager.isSelected(
                dynamic_cast<const tracktion_engine::Selectable *>(multiTrackViewModel.listViewModel.getAdapter()->getItemAtIndex(0))), true);

    }

    TEST_F(TracksListViewModelTest, addTrackZeroTrack)
    {

        MockEditItemListViewModelListener listListener;
        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(-1))
                .Times(1);

        EXPECT_CALL(listListener, selectedIndexChanged(0))
                .Times(1);

        zeroTrackViewModel.listViewModel.addListener(&listListener);
        EXPECT_EQ(zeroTrackViewModel.listViewModel.getAdapter()->size(), 0);
        zeroTrackViewModel.addTrack();
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(zeroTrackViewModel.listViewModel.getAdapter()->size(), 1);
        EXPECT_EQ(zeroTrackSelectionManager.isSelected(
                dynamic_cast<const tracktion_engine::Selectable *>(zeroTrackViewModel.listViewModel.getAdapter()->getItemAtIndex(0))), true);

    }

    TEST_F(TracksListViewModelTest, addTrackSingleTrack)
    {

        MockEditItemListViewModelListener listListener;
        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listListener, selectedIndexChanged(1))
                .Times(1);

        singleTrackViewModel.listViewModel.addListener(&listListener);
        singleTrackViewModel.addTrack();
        singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackViewModel.listViewModel.getAdapter()->size(), 2);
        EXPECT_EQ(singleTrackSelectionManager.isSelected(
                dynamic_cast<const tracktion_engine::Selectable *>(singleTrackViewModel.listViewModel.getAdapter()->getItemAtIndex(1))), true);

    }

    TEST_F(TracksListViewModelTest, addTrackMultiTrack)
    {

        MockEditItemListViewModelListener listListener;
        // called when listener is added
        EXPECT_CALL(listListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listListener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listListener, selectedIndexChanged(8))
                .Times(1);

        multiTrackViewModel.listViewModel.addListener(&listListener);
        multiTrackViewModel.addTrack();
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackViewModel.listViewModel.getAdapter()->size(), 9);
        EXPECT_EQ(multiTrackSelectionManager.isSelected(
                dynamic_cast<const tracktion_engine::Selectable *>(multiTrackViewModel.listViewModel.getAdapter()->getItemAtIndex(8))), true);

    }

    TEST_F(TracksListViewModelTest, startPlayingStopPlaying)
    {

        MockTracksListViewModelListener listener;

        EXPECT_CALL(listener, isPlayingChanged(true)).Times(1);

        // called once when we add the listener and again when we stop playing
        EXPECT_CALL(listener, isPlayingChanged(false)).Times(2);

        singleTrackViewModel.addListener(&listener);

        singleTrackViewModel.startPlaying();
        singleTrackEdit->getTransport().sendSynchronousChangeMessage();
        EXPECT_EQ(singleTrackEdit->getTransport().isPlaying(), true);

        singleTrackViewModel.stopRecordingOrPlaying();
        singleTrackEdit->getTransport().sendSynchronousChangeMessage();
        EXPECT_EQ(singleTrackEdit->getTransport().isPlaying(), false);

    }

    TEST_F(TracksListViewModelTest, stopPlayingWhenAlreadyStopped)
    {

        MockTracksListViewModelListener listener;

        // called once when we add the listener and again when we stop playing
        EXPECT_CALL(listener, isPlayingChanged(false)).Times(2);

        singleTrackViewModel.addListener(&listener);

        // move playhead forward in time a bit
        singleTrackEdit->getTransport().setCurrentPosition(1.0);
        singleTrackViewModel.stopRecordingOrPlaying();
        singleTrackEdit->getTransport().sendSynchronousChangeMessage();
        EXPECT_FLOAT_EQ(singleTrackEdit->getTransport().getCurrentPosition(), 0.0);

    }

    TEST_F(TracksListViewModelTest, tracksViewTypeChange)
    {

        MockTracksListViewModelListener listener;

        // called when listener is added
        EXPECT_CALL(listener, tracksViewTypeChanged(app_view_models::TracksListViewModel::TracksViewType::MULTI_TRACK)).Times(1);

        EXPECT_CALL(listener, tracksViewTypeChanged(app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK)).Times(1);

        singleTrackViewModel.addListener(&listener);

        singleTrackViewModel.setTracksViewType(app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK);
        singleTrackViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TracksListViewModelTest, nudgeForward)
    {

        double position = singleTrackEdit->getTransport().getCurrentPosition();
        singleTrackViewModel.nudgeTransportForward();
        EXPECT_FLOAT_EQ(singleTrackEdit->getTransport().getCurrentPosition(), position + singleTrackCamera.getNudgeAmount());

    }

    TEST_F(TracksListViewModelTest, nudgeBackward)
    {

        double position = singleTrackEdit->getTransport().getCurrentPosition();
        singleTrackViewModel.nudgeTransportBackward();
        EXPECT_EQ(singleTrackEdit->getTransport().getCurrentPosition(), position);

        singleTrackEdit->getTransport().setCurrentPosition(1.0);
        position = singleTrackEdit->getTransport().getCurrentPosition();
        singleTrackViewModel.nudgeTransportBackward();
        EXPECT_FLOAT_EQ(singleTrackEdit->getTransport().getCurrentPosition(), position - singleTrackCamera.getNudgeAmount());

    }

    TEST_F(TracksListViewModelTest, edgeScrollForward)
    {


        singleTrackEdit->getTransport().setCurrentPosition(singleTrackCamera.getCenter() + singleTrackCamera.getCenterOffsetLimit());
        double cameraCenter = singleTrackCamera.getCenter();
        singleTrackViewModel.nudgeTransportForward();
        singleTrackEdit->getTransport().dispatchPendingMessages();
        EXPECT_FLOAT_EQ(singleTrackCamera.getCenter(), cameraCenter + singleTrackCamera.getNudgeAmount());

    }

    TEST_F(TracksListViewModelTest, edgeScrollBackward)
    {


        singleTrackCamera.setCenter(3 * singleTrackCamera.getCenter());
        singleTrackEdit->getTransport().setCurrentPosition(singleTrackCamera.getCenter() - singleTrackCamera.getCenterOffsetLimit());
        double cameraCenter = singleTrackCamera.getCenter();
        singleTrackViewModel.nudgeTransportBackward();
        singleTrackEdit->getTransport().dispatchPendingMessages();
        EXPECT_FLOAT_EQ(singleTrackCamera.getCenter(), cameraCenter - singleTrackCamera.getNudgeAmount());

    }

}