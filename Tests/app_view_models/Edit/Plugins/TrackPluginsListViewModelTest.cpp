#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "../EditItemList/MockEditItemListViewModelListener.h"

namespace AppViewModelsTests {

    class TrackPluginsListViewModelTest : public ::testing::Test {
    protected:

        TrackPluginsListViewModelTest()
                : singlePluginSelectionManager(engine),
                  multiPluginSelectionManager(engine),
                  zeroPluginSelectionManager(engine),
                  singlePluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  zeroPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singlePluginViewModel(tracktion_engine::getAudioTracks(*singlePluginEdit)[0],
                                        singlePluginSelectionManager),
                  multiPluginViewModel(tracktion_engine::getAudioTracks(*multiPluginEdit)[0],
                                       multiPluginSelectionManager),
                  zeroPluginViewModel(tracktion_engine::getAudioTracks(*zeroPluginEdit)[0],
                                      zeroPluginSelectionManager) {}

        void SetUp() override {

            // flush any updates
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();


            // double calls to handle update is necessary since
            // selected index change is dispatched when a pluginChange occurrs
            // so you have to call it once to handle the plugin change
            // then again to handle the selection change the the plugin change
            // triggers
            tracktion_engine::getAudioTracks(*singlePluginEdit)[0]
                    ->pluginList.getPlugins().getObjectPointerUnchecked(1)->removeFromParent();
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();

            tracktion_engine::getAudioTracks(*zeroPluginEdit)[0]
                    ->pluginList.getPlugins()[1]->removeFromParent();
            zeroPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            tracktion_engine::getAudioTracks(*zeroPluginEdit)[0]
                    ->pluginList.getPlugins()[0]->removeFromParent();
            zeroPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.listViewModel.handleUpdateNowIfNeeded();


        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager singlePluginSelectionManager;
        tracktion_engine::SelectionManager multiPluginSelectionManager;
        tracktion_engine::SelectionManager zeroPluginSelectionManager;
        std::unique_ptr<tracktion_engine::Edit> singlePluginEdit;
        std::unique_ptr<tracktion_engine::Edit> multiPluginEdit;
        std::unique_ptr<tracktion_engine::Edit> zeroPluginEdit;
        app_view_models::TrackPluginsListViewModel singlePluginViewModel;
        app_view_models::TrackPluginsListViewModel multiPluginViewModel;
        app_view_models::TrackPluginsListViewModel zeroPluginViewModel;

    };

    TEST_F(TrackPluginsListViewModelTest, deleteSelectedPluginSinglePlugin)
    {
    
        MockEditItemListViewModelListener listener;

        // Called once when listener is added and again when plugin is deleted
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(-1))
                .Times(1);


        singlePluginViewModel.listViewModel.addListener(&listener);
        singlePluginViewModel.deleteSelectedPlugin();
        singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();
        singlePluginViewModel.listViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(singlePluginViewModel.listViewModel.getSelectedItemIndex(), -1);
        EXPECT_EQ(singlePluginViewModel.listViewModel.getAdapter()->size(), 0);
    
    }

    TEST_F(TrackPluginsListViewModelTest, deleteSelectedPluginMultiPlugin)
    {

        MockEditItemListViewModelListener listener;

        // Called once when listener is added and again when plugin is deleted
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        multiPluginViewModel.listViewModel.addListener(&listener);
        multiPluginViewModel.deleteSelectedPlugin();
        multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();
        multiPluginViewModel.listViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiPluginViewModel.listViewModel.getSelectedItemIndex(), 0);
        EXPECT_EQ(multiPluginViewModel.listViewModel.getAdapter()->size(), 1);

    }



}