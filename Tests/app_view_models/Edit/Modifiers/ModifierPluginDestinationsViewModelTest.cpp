#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"
#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class ModifiersPluginDestinationsViewModelTest : public ::testing::Test {
  protected:
    ModifiersPluginDestinationsViewModelTest()
        : edit(tracktion::Edit::createSingleTrackEdit(engine)),
          viewModel(tracktion::getAudioTracks(*edit)[0]) {}

    void SetUp() override {
        // flush any updates
        viewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
    }

    tracktion::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion::Edit> edit;
    app_view_models::ModifierPluginDestinationsViewModel viewModel;
};

TEST_F(ModifiersPluginDestinationsViewModelTest, getItemNames) {
    // Should be 2 default track plugins
    EXPECT_EQ(viewModel.listViewModel.getItemNames().size(), 2);
}

TEST_F(ModifiersPluginDestinationsViewModelTest, getSelectedItem) {
    EXPECT_EQ(viewModel.listViewModel.getSelectedItem()->getName(),
              juce::String("Volume & Pan Plugin"));
}

} // namespace AppViewModelsTests
