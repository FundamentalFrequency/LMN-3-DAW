#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"

namespace AppViewModelsTests {

    class AvailablePluginParametersListViewModelTest : public ::testing::Test {
    protected:

        AvailablePluginParametersListViewModelTest()
                : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  viewModel(tracktion_engine::getAudioTracks(*edit)[0], tracktion_engine::getAudioTracks(*edit)[0]->getVolumePlugin()) {}

        void SetUp() override {

            // flush any updates
            viewModel.itemListState.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::AvailablePluginParametersListViewModel viewModel;

    };

    TEST_F(AvailablePluginParametersListViewModelTest, getItemNames)
    {

        // Should be 2 default track plugins
        EXPECT_EQ(viewModel.getItemNames().size(), 2);

    }

    TEST_F(AvailablePluginParametersListViewModelTest, getSelectedItem)
    {

        EXPECT_EQ(viewModel.getSelectedItem()->getParameterName(), juce::String("Volume"));

    }

}
