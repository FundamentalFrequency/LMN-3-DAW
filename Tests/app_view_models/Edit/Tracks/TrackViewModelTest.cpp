#include "MockTrackViewModelListener.h"
#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class TrackViewModelTest : public ::testing::Test {
  protected:
    TrackViewModelTest()
        : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
          camera(7),
          viewModel(tracktion_engine::getAudioTracks(*edit)[0], camera) {}

    void SetUp() override {

        // flush any pending updates
        viewModel.handleUpdateNowIfNeeded();
    }

    tracktion_engine::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion_engine::Edit> edit;
    app_services::TimelineCamera camera;
    app_view_models::TrackViewModel viewModel;
};

using ::testing::_;
TEST_F(TrackViewModelTest, clipAdded) {

    MockTrackViewModelListener listener;
    // called once when added listener added, once again when clip added
    EXPECT_CALL(listener, clipsChanged(_)).Times(2);

    viewModel.addListener(&listener);

    auto track = tracktion_engine::getAudioTracks(*edit)[0];
    EXPECT_EQ(track->getClips().size(), 0);
    track->insertNewClip(tracktion_engine::TrackItem::Type::midi, {0, 1},
                         nullptr);
    viewModel.handleUpdateNowIfNeeded();
    EXPECT_EQ(track->getClips().size(), 1);
}

TEST_F(TrackViewModelTest, clipRemoved) {

    MockTrackViewModelListener listener;
    // called once when added listener added, once again when clip deleted
    EXPECT_CALL(listener, clipsChanged(_)).Times(2);

    auto track = tracktion_engine::getAudioTracks(*edit)[0];
    track->insertNewClip(tracktion_engine::TrackItem::Type::midi, {0, 1},
                         nullptr);
    EXPECT_EQ(track->getClips().size(), 1);
    viewModel.addListener(&listener);

    auto clip = track->getClips()[0];
    clip->removeFromParentTrack();
    viewModel.handleUpdateNowIfNeeded();

    EXPECT_EQ(track->getClips().size(), 0);
}

TEST_F(TrackViewModelTest, clipPositionChanged) {

    MockTrackViewModelListener listener;
    // called once when added listener added, once again when clip end time
    // changed
    EXPECT_CALL(listener, clipPositionsChanged(_)).Times(2);

    auto track = tracktion_engine::getAudioTracks(*edit)[0];
    track->insertNewClip(tracktion_engine::TrackItem::Type::midi, {0, 1},
                         nullptr);
    viewModel.addListener(&listener);

    auto clip = track->getClips()[0];
    clip->setEnd(10, false);
    viewModel.handleUpdateNowIfNeeded();
}

TEST_F(TrackViewModelTest, transportChanged) {

    MockTrackViewModelListener listener;
    // called once when added listener added, once when recording is started
    EXPECT_CALL(listener, transportChanged()).Times(2);

    viewModel.addListener(&listener);
    auto track = tracktion_engine::getAudioTracks(*edit)[0];
    track->edit.getTransport().sendSynchronousChangeMessage();
    viewModel.handleUpdateNowIfNeeded();
}

} // namespace AppViewModelsTests