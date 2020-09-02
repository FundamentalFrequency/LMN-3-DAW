#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"

namespace AppViewModelsTests {

    class TrackModifiersListViewModelTest : public ::testing::Test {
    protected:

        TrackModifiersListViewModelTest()
                : selectionManager(engine),
                  edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  viewModel(tracktion_engine::getAudioTracks(*edit)[0],
                                      selectionManager) {}

        void SetUp() override {

            // flush any updates
            viewModel.listViewModel.handleUpdateNowIfNeeded();
            viewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

            // double calls to handle update is necessary since
            // selected index change is dispatched when a itemChange occurrs
            // so you have to call it once to handle the item change
            // then again to handle the selection change the the item change
            // triggers
            tracktion_engine::getAudioTracks(*edit)[0]
                    ->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::LFO), 0, nullptr);
            viewModel.listViewModel.handleUpdateNowIfNeeded();
            viewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

            tracktion_engine::getAudioTracks(*edit)[0]
                    ->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::RANDOM), 0, nullptr);
            viewModel.listViewModel.handleUpdateNowIfNeeded();
            viewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager selectionManager;
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::TrackModifiersListViewModel viewModel;

    };

    TEST_F(TrackModifiersListViewModelTest, deleteSelectedModifier)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener listStateListener;

        // Called once when listener is added and again when plugin is deleted
        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listStateListener, selectedIndexChanged(0))
                .Times(1);

        viewModel.listViewModel.addListener(&editItemListViewModelListener);
        viewModel.listViewModel.itemListState.addListener(&listStateListener);
        viewModel.deleteSelectedModifier();
        viewModel.listViewModel.handleUpdateNowIfNeeded();
        viewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(viewModel.listViewModel.itemListState.getSelectedItemIndex(), 0);
        EXPECT_EQ(viewModel.listViewModel.itemListState.listSize, 1);


    }


}