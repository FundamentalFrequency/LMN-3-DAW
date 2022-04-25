#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"

namespace AppViewModelsTests {

    class TrackPluginsListViewModelTest : public ::testing::Test {
    protected:

        TrackPluginsListViewModelTest()
                : singlePluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singlePluginViewModel(tracktion_engine::getAudioTracks(*singlePluginEdit)[0]),
                  multiPluginViewModel(tracktion_engine::getAudioTracks(*multiPluginEdit)[0]),
                  singlePluginGroup(*singlePluginEdit),
                  multiPluginGroup(*multiPluginEdit)
        {}

        void SetUp() override {

            // Add 2 effects from the plugin effects group to the track
            // we will add the equaliser and the Reverb
            // effects is group at index 1
            auto singlePluginTrack = tracktion_engine::getAudioTracks(*singlePluginEdit)[0];
            if (auto selectedPluginItem = dynamic_cast<app_view_models::PluginTreeItem*>(singlePluginGroup.getSubItem(1)->getSubItem(0)))
                singlePluginTrack->pluginList.insertPlugin(selectedPluginItem->create(singlePluginTrack->edit), -1, nullptr);

            auto multiPluginTrack = tracktion_engine::getAudioTracks(*multiPluginEdit)[0];
            if (auto selectedPluginItem = dynamic_cast<app_view_models::PluginTreeItem*>(multiPluginGroup.getSubItem(1)->getSubItem(0)))
                multiPluginTrack->pluginList.insertPlugin(selectedPluginItem->create(multiPluginTrack->edit), -1, nullptr);
            if (auto selectedPluginItem = dynamic_cast<app_view_models::PluginTreeItem*>(multiPluginGroup.getSubItem(1)->getSubItem(1)))
                multiPluginTrack->pluginList.insertPlugin(selectedPluginItem->create(multiPluginTrack->edit), -1, nullptr);

            // flush any updates
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            singlePluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
            multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            multiPluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> singlePluginEdit;
        std::unique_ptr<tracktion_engine::Edit> multiPluginEdit;
        app_view_models::TrackPluginsListViewModel singlePluginViewModel;
        app_view_models::TrackPluginsListViewModel multiPluginViewModel;
        app_view_models::PluginTreeGroup singlePluginGroup;
        app_view_models::PluginTreeGroup multiPluginGroup;



    };

    TEST_F(TrackPluginsListViewModelTest, deleteSelectedPluginSinglePlugin)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener listStateListener;

        // Called once when listener is added and again when plugin is deleted
        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listStateListener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listStateListener, selectedIndexChanged(-1))
                .Times(1);


        singlePluginViewModel.listViewModel.addListener(&editItemListViewModelListener);
        singlePluginViewModel.listViewModel.itemListState.addListener(&listStateListener);

        singlePluginViewModel.deleteSelectedPlugin();
        singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
        singlePluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(singlePluginViewModel.listViewModel.itemListState.getSelectedItemIndex(), -1);
        EXPECT_EQ(singlePluginViewModel.listViewModel.itemListState.listSize, 0);
    
    }

    TEST_F(TrackPluginsListViewModelTest, deleteSelectedPluginMultiPlugin)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener listStateListener;

        // Called once when listener is added and again when plugin is deleted
        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listStateListener, selectedIndexChanged(0))
                .Times(1);

        multiPluginViewModel.listViewModel.addListener(&editItemListViewModelListener);
        multiPluginViewModel.listViewModel.itemListState.addListener(&listStateListener);

        multiPluginViewModel.deleteSelectedPlugin();
        multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
        multiPluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiPluginViewModel.listViewModel.itemListState.getSelectedItemIndex(), 0);
        EXPECT_EQ(multiPluginViewModel.listViewModel.itemListState.listSize, 1);

    }



}