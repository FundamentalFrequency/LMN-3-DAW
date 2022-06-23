#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class StepSequencerViewModelTest : public ::testing::Test {
  protected:
    StepSequencerViewModelTest()
        : edit(tracktion::Edit::createSingleTrackEdit(engine)),
          editViewModel(*edit),
          viewModel(tracktion::getAudioTracks(*edit)[0]) {}

    void SetUp() override {}

    tracktion::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion::Edit> edit;
    // The edit VM is necessary since the
    // EDIT_VIEW_STATE is used in the step seq VM
    app_view_models::EditViewModel editViewModel;
    app_view_models::StepSequencerViewModel viewModel;
};

TEST_F(StepSequencerViewModelTest, getNumChannels) {
    EXPECT_EQ(viewModel.getNumChannels(), 24);
}

TEST_F(StepSequencerViewModelTest, getNumNotesPerChannel) {
    EXPECT_EQ(viewModel.getNumNotesPerChannel(), 16);
}

} // namespace AppViewModelsTests