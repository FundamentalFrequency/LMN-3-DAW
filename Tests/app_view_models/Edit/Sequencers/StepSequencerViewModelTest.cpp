#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class StepSequencerViewModelTest : public ::testing::Test {
  protected:
    StepSequencerViewModelTest()
        : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
          viewModel(tracktion_engine::getAudioTracks(*edit)[0]) {}

    void SetUp() override {}

    tracktion_engine::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion_engine::Edit> edit;
    app_view_models::StepSequencerViewModel viewModel;
};

TEST_F(StepSequencerViewModelTest, getNumChannels) {
    EXPECT_EQ(viewModel.getNumChannels(), 24);
}

TEST_F(StepSequencerViewModelTest, getNumNotesPerChannel) {
    EXPECT_EQ(viewModel.getNumNotesPerChannel(), 16);
}

} // namespace AppViewModelsTests