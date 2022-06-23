#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"
#include "MockTracksListViewModelListener.h"
#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class TracksListViewModelTest : public ::testing::Test {
  protected:
    TracksListViewModelTest()
        : singleTrackEdit(tracktion::Edit::createSingleTrackEdit(engine)),
          multiTrackEdit(tracktion::Edit::createSingleTrackEdit(engine)),
          zeroTrackEdit(tracktion::Edit::createSingleTrackEdit(engine)),
          singleTrackCamera(7.0), multiTrackCamera(7.0), zeroTrackCamera(7.0),
          singleTrackViewModel(*singleTrackEdit, singleTrackCamera),
          multiTrackViewModel(*multiTrackEdit, multiTrackCamera),
          zeroTrackViewModel(*zeroTrackEdit, zeroTrackCamera) {}

    void SetUp() override {
        singleTrackViewModel.handleUpdateNowIfNeeded();
        multiTrackViewModel.handleUpdateNowIfNeeded();
        zeroTrackViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();

        singleTrackViewModel.listViewModel.itemListState
            .handleUpdateNowIfNeeded();
        multiTrackViewModel.listViewModel.itemListState
            .handleUpdateNowIfNeeded();
        zeroTrackViewModel.listViewModel.itemListState
            .handleUpdateNowIfNeeded();

        multiTrackEdit->ensureNumberOfAudioTracks(8);
        multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets
        // pushed out in the handleAsyncUpdate after an item gets added
        multiTrackViewModel.listViewModel.itemListState
            .handleUpdateNowIfNeeded();

        zeroTrackEdit->deleteTrack(
            tracktion::getAudioTracks(*zeroTrackEdit)[0]);
        zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets
        // pushed out in the handleAsyncUpdate after an item gets added
        zeroTrackViewModel.listViewModel.itemListState
            .handleUpdateNowIfNeeded();
    }

    tracktion::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion::Edit> singleTrackEdit;
    std::unique_ptr<tracktion::Edit> multiTrackEdit;
    std::unique_ptr<tracktion::Edit> zeroTrackEdit;
    app_services::TimelineCamera singleTrackCamera;
    app_services::TimelineCamera multiTrackCamera;
    app_services::TimelineCamera zeroTrackCamera;
    app_view_models::TracksListViewModel singleTrackViewModel;
    app_view_models::TracksListViewModel multiTrackViewModel;
    app_view_models::TracksListViewModel zeroTrackViewModel;
};

using ::testing::_;
TEST_F(TracksListViewModelTest, deleteSelectedTrackZeroTrack) {
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(1);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(-1)).Times(1);

    zeroTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    zeroTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);

    zeroTrackViewModel.deleteSelectedTrack();
    zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    zeroTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    EXPECT_EQ(zeroTrackViewModel.listViewModel.itemListState.listSize, 0);
}

TEST_F(TracksListViewModelTest, deleteSelectedTrackSingleTrack) {
    // Cannot delete the only remaining track
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(1);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(0)).Times(1);

    singleTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    singleTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);
    singleTrackViewModel.deleteSelectedTrack();
    singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    singleTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

    EXPECT_EQ(singleTrackViewModel.listViewModel.itemListState.listSize, 1);
}

TEST_F(TracksListViewModelTest, deleteSelectedTrackMultiTrack) {
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(2);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(0)).Times(1);

    multiTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    multiTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);

    multiTrackViewModel.deleteSelectedTrack();
    multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    multiTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    EXPECT_EQ(multiTrackViewModel.listViewModel.itemListState.listSize, 7);
}

TEST_F(TracksListViewModelTest, addTrackZeroTrack) {
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(2);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(-1)).Times(1);

    EXPECT_CALL(listStateListener, selectedIndexChanged(0)).Times(1);

    zeroTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    zeroTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);

    EXPECT_EQ(zeroTrackViewModel.listViewModel.itemListState.listSize, 0);
    zeroTrackViewModel.addTrack();
    zeroTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    zeroTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    EXPECT_EQ(zeroTrackViewModel.listViewModel.itemListState.listSize, 1);
}

TEST_F(TracksListViewModelTest, addTrackSingleTrack) {
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(2);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(0)).Times(1);

    EXPECT_CALL(listStateListener, selectedIndexChanged(1)).Times(1);

    singleTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    singleTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);
    singleTrackViewModel.addTrack();
    singleTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    singleTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    EXPECT_EQ(singleTrackViewModel.listViewModel.itemListState.listSize, 2);
}

TEST_F(TracksListViewModelTest, addTrackMultiTrack) {
    MockEditItemListViewModelListener editItemListViewModelListener;
    MockItemListStateListener listStateListener;

    // called when listener is added
    EXPECT_CALL(editItemListViewModelListener, itemsChanged()).Times(2);

    // called when listener is added
    EXPECT_CALL(listStateListener, selectedIndexChanged(0)).Times(1);

    EXPECT_CALL(listStateListener, selectedIndexChanged(8)).Times(1);

    multiTrackViewModel.listViewModel.addListener(
        &editItemListViewModelListener);
    multiTrackViewModel.listViewModel.itemListState.addListener(
        &listStateListener);

    multiTrackViewModel.addTrack();
    multiTrackViewModel.listViewModel.handleUpdateNowIfNeeded();
    multiTrackViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    EXPECT_EQ(multiTrackViewModel.listViewModel.itemListState.listSize, 9);
}

TEST_F(TracksListViewModelTest, startPlayingStopPlaying) {
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

TEST_F(TracksListViewModelTest, stopPlayingWhenAlreadyStopped) {
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

TEST_F(TracksListViewModelTest, tracksViewTypeChange) {
    MockTracksListViewModelListener listener;

    // called when listener is added
    EXPECT_CALL(
        listener,
        tracksViewTypeChanged(
            app_view_models::TracksListViewModel::TracksViewType::MULTI_TRACK))
        .Times(1);

    EXPECT_CALL(
        listener,
        tracksViewTypeChanged(
            app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK))
        .Times(1);

    singleTrackViewModel.addListener(&listener);

    singleTrackViewModel.setTracksViewType(
        app_view_models::TracksListViewModel::TracksViewType::SINGLE_TRACK);
    singleTrackViewModel.handleUpdateNowIfNeeded();
}

TEST_F(TracksListViewModelTest, nudgeForward) {
    double position = singleTrackEdit->getTransport().getCurrentPosition();
    singleTrackViewModel.nudgeTransportForward();
    EXPECT_FLOAT_EQ(singleTrackEdit->getTransport().getCurrentPosition(),
                    position + singleTrackCamera.getNudgeAmount());
}

TEST_F(TracksListViewModelTest, nudgeBackward) {
    double position = singleTrackEdit->getTransport().getCurrentPosition();
    singleTrackViewModel.nudgeTransportBackward();
    EXPECT_EQ(singleTrackEdit->getTransport().getCurrentPosition(), position);

    singleTrackEdit->getTransport().setCurrentPosition(1.0);
    position = singleTrackEdit->getTransport().getCurrentPosition();
    singleTrackViewModel.nudgeTransportBackward();
    EXPECT_FLOAT_EQ(singleTrackEdit->getTransport().getCurrentPosition(),
                    position - singleTrackCamera.getNudgeAmount());
}

TEST_F(TracksListViewModelTest, edgeScrollForward) {
    singleTrackEdit->getTransport().setCurrentPosition(
        singleTrackCamera.getCenter() +
        singleTrackCamera.getCenterOffsetLimit());
    double cameraCenter = singleTrackCamera.getCenter();
    singleTrackViewModel.nudgeTransportForward();
    singleTrackEdit->getTransport().dispatchPendingMessages();
    EXPECT_FLOAT_EQ(singleTrackCamera.getCenter(),
                    cameraCenter + singleTrackCamera.getNudgeAmount());
}

TEST_F(TracksListViewModelTest, edgeScrollBackward) {
    singleTrackCamera.setCenter(3 * singleTrackCamera.getCenter());
    singleTrackEdit->getTransport().setCurrentPosition(
        singleTrackCamera.getCenter() -
        singleTrackCamera.getCenterOffsetLimit());
    double cameraCenter = singleTrackCamera.getCenter();
    singleTrackViewModel.nudgeTransportBackward();
    singleTrackEdit->getTransport().dispatchPendingMessages();
    EXPECT_FLOAT_EQ(singleTrackCamera.getCenter(),
                    cameraCenter - singleTrackCamera.getNudgeAmount());
}

TEST_F(TracksListViewModelTest,
       deleteSelectedTracksClipAtPlayHeadWithPlayHeadAtStartOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackViewModel.cutSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 0);
}

TEST_F(TracksListViewModelTest,
       deleteSelectedTracksClipAtPlayHeadWithPlayHeadAtEndOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackEdit->getTransport().setCurrentPosition(.99);
    singleTrackViewModel.cutSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 0);
}

TEST_F(TracksListViewModelTest,
       deleteSelectedTracksClipAtPlayHeadWithPlayHeadAtMiddleOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackEdit->getTransport().setCurrentPosition(.5);
    singleTrackViewModel.cutSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 0);
}

TEST_F(TracksListViewModelTest,
       deleteSelectedTracksClipAtPlayHeadWithPlayHeadOutsideOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackEdit->getTransport().setCurrentPosition(1.01);
    singleTrackViewModel.cutSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 1);
}

TEST_F(TracksListViewModelTest,
       splitSelectedTracksClipAtPlayHeadWithPlayHeadAtMiddleOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackEdit->getTransport().setCurrentPosition(.5);
    singleTrackViewModel.splitSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 2);
}

TEST_F(TracksListViewModelTest,
       splitSelectedTracksClipAtPlayHeadWithPlayHeadOutsideOfCLip) {
    auto track = tracktion::getAudioTracks(*singleTrackEdit)[0];
    track->insertNewClip(tracktion::TrackItem::Type::midi,
                         {tracktion::TimePosition::fromSeconds(0),
                          tracktion::TimePosition::fromSeconds(1)},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    singleTrackEdit->getTransport().setCurrentPosition(1.01);
    singleTrackViewModel.splitSelectedTracksClipAtPlayHead();
    EXPECT_EQ(track->getClips().size(), 1);
}

} // namespace AppViewModelsTests