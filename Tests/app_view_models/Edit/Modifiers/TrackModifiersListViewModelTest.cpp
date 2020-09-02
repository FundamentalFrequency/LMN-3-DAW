#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../EditItemList/MockEditItemListViewModelListener.h"

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


            // double calls to handle update is necessary since
            // selected index change is dispatched when a itemChange occurrs
            // so you have to call it once to handle the item change
            // then again to handle the selection change the the item change
            // triggers
            tracktion_engine::getAudioTracks(*edit)[0]
                    ->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::LFO), 0, nullptr);
            viewModel.listViewModel.handleUpdateNowIfNeeded();
            viewModel.listViewModel.handleUpdateNowIfNeeded();

            tracktion_engine::getAudioTracks(*edit)[0]
                    ->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::RANDOM), 0, nullptr);
            viewModel.listViewModel.handleUpdateNowIfNeeded();
            viewModel.listViewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager selectionManager;
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::TrackModifiersListViewModel viewModel;

    };

    TEST_F(TrackModifiersListViewModelTest, deleteSelectedModifier)
    {

//        MockEditItemListViewModelListener listener;
//
//        // Called once when listener is added and again when plugin is deleted
//        EXPECT_CALL(listener, itemsChanged())
//                .Times(2);
//
//        // called when listener is added
//        EXPECT_CALL(listener, selectedIndexChanged(0))
//                .Times(1);
//
//        viewModel.listViewModel.addListener(&listener);
//        viewModel.deleteSelectedModifier();
//        viewModel.listViewModel.handleUpdateNowIfNeeded();
//        viewModel.listViewModel.handleUpdateNowIfNeeded();
//
//        EXPECT_EQ(viewModel.listViewModel.getSelectedItemIndex(), 0);
//        EXPECT_EQ(viewModel.listViewModel.getAdapter()->size(), 1);


    }


}