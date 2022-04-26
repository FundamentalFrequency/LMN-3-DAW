#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"
#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class AvailableModifiersListViewModelTest : public ::testing::Test {
  protected:
    AvailableModifiersListViewModelTest()
        : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
          viewModel(tracktion_engine::getAudioTracks(*edit)[0]) {}

    void SetUp() override {
        // flush any updates
        viewModel.itemListState.handleUpdateNowIfNeeded();
    }

    tracktion_engine::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion_engine::Edit> edit;
    app_view_models::AvailableModifiersListViewModel viewModel;
};

TEST_F(AvailableModifiersListViewModelTest, getItemNames) {
    EXPECT_GT(viewModel.getItemNames().size(), 0);
}

TEST_F(AvailableModifiersListViewModelTest, getSelectedItem) {
    EXPECT_EQ(viewModel.getSelectedItem().name, juce::String("LFO Modifier"));
    EXPECT_EQ(viewModel.getSelectedItem().identifier,
              tracktion_engine::IDs::LFO);
}

} // namespace AppViewModelsTests
