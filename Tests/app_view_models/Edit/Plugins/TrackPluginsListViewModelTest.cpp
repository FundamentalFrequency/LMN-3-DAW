#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../ItemList/MockEditItemListViewModelListener.h"
#include "../ItemList/MockItemListStateListener.h"

namespace AppViewModelsTests {

    class TrackPluginsListViewModelTest : public ::testing::Test {
    protected:

        TrackPluginsListViewModelTest()
                : singlePluginSelectionManager(engine),
                  multiPluginSelectionManager(engine),
                  singlePluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singlePluginViewModel(tracktion_engine::getAudioTracks(*singlePluginEdit)[0],
                                        singlePluginSelectionManager),
                  multiPluginViewModel(tracktion_engine::getAudioTracks(*multiPluginEdit)[0],
                                       multiPluginSelectionManager)
        {}

        void SetUp() override {

            // flush any updates
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            singlePluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();
            multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            multiPluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();


            // double calls to handle update is necessary since
            // selected index change is dispatched when a pluginChange occurrs
            // so you have to call it once to handle the plugin change
            // then again to handle the selection change the the plugin change
            // triggers
            tracktion_engine::getAudioTracks(*singlePluginEdit)[0]
                    ->pluginList.getPlugins().getObjectPointerUnchecked(1)->removeFromParent();
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            singlePluginViewModel.listViewModel.itemListState.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager singlePluginSelectionManager;
        tracktion_engine::SelectionManager multiPluginSelectionManager;
        std::unique_ptr<tracktion_engine::Edit> singlePluginEdit;
        std::unique_ptr<tracktion_engine::Edit> multiPluginEdit;
        app_view_models::TrackPluginsListViewModel singlePluginViewModel;
        app_view_models::TrackPluginsListViewModel multiPluginViewModel;


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