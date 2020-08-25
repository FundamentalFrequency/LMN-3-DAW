#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockTrackPluginsViewModelListener.h"


namespace AppViewModelsTests {

    class TrackPluginsViewModelTest : public ::testing::Test {
    protected:

        TrackPluginsViewModelTest()
                : singlePluginSelectionManager(engine),
                  multiPluginSelectionManager(engine),
                  zeroPluginSelectionManager(engine),
                  singlePluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  zeroPluginEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singlePluginViewModel(tracktion_engine::getAudioTracks(*singlePluginEdit)[0], singlePluginSelectionManager),
                  multiPluginViewModel(tracktion_engine::getAudioTracks(*multiPluginEdit)[0], multiPluginSelectionManager),
                  zeroPluginViewModel(tracktion_engine::getAudioTracks(*zeroPluginEdit)[0], zeroPluginSelectionManager)

        {}

        void SetUp() override
        {

            // flush any updates
            singlePluginViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.handleUpdateNowIfNeeded();
            multiPluginViewModel.handleUpdateNowIfNeeded();


            // double calls to handle update is necessary since
            // selected index change is dispatched when a pluginChange occurrs
            // so you have to call it once to handle the plugin change
            // then again to handle the selection change the the plugin change
            // triggers
            tracktion_engine::getAudioTracks(*singlePluginEdit)[0]
                ->pluginList.getPlugins().getObjectPointerUnchecked(1)->removeFromParent();
            singlePluginViewModel.handleUpdateNowIfNeeded();
            singlePluginViewModel.handleUpdateNowIfNeeded();

            tracktion_engine::getAudioTracks(*zeroPluginEdit)[0]
                    ->pluginList.getPlugins()[1]->removeFromParent();
            zeroPluginViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.handleUpdateNowIfNeeded();
            tracktion_engine::getAudioTracks(*zeroPluginEdit)[0]
                    ->pluginList.getPlugins()[0]->removeFromParent();
            zeroPluginViewModel.handleUpdateNowIfNeeded();
            zeroPluginViewModel.handleUpdateNowIfNeeded();


        }

        tracktion_engine::Engine engine {"ENGINE"};
        tracktion_engine::SelectionManager singlePluginSelectionManager;
        tracktion_engine::SelectionManager multiPluginSelectionManager;
        tracktion_engine::SelectionManager zeroPluginSelectionManager;
        std::unique_ptr<tracktion_engine::Edit> singlePluginEdit;
        std::unique_ptr<tracktion_engine::Edit> multiPluginEdit;
        std::unique_ptr<tracktion_engine::Edit> zeroPluginEdit;
        app_view_models::TrackPluginsViewModel singlePluginViewModel;
        app_view_models::TrackPluginsViewModel multiPluginViewModel;
        app_view_models::TrackPluginsViewModel zeroPluginViewModel;

    };



    TEST_F(TrackPluginsViewModelTest, initialSelectedPluginIndex)
    {

        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0) << "incorrect initial track index for single plugin track";
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0) << "incorrect initial track index for multi-plugin track";
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1) << "incorrect initial track index for zero-plugin track";

    }

    TEST_F(TrackPluginsViewModelTest, setSelectedPluginIndexSinglePlugin)
    {

        // Single Track
        singlePluginViewModel.setSelectedPluginIndex(-1);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(-2);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(-100);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(0);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(2);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);
        singlePluginViewModel.setSelectedPluginIndex(100);
        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, setSelectedPluginIndexMultiPlugin)
    {
        // Multi-Track has 2 plugins initially
        // volume and pan and level meter
        multiPluginViewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 1);
        multiPluginViewModel.setSelectedPluginIndex(-1);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0);
        multiPluginViewModel.setSelectedPluginIndex(-2);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0);
        multiPluginViewModel.setSelectedPluginIndex(-100);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0);
        multiPluginViewModel.setSelectedPluginIndex(0);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0);
        multiPluginViewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 1);
        multiPluginViewModel.setSelectedPluginIndex(2);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 1);
        multiPluginViewModel.setSelectedPluginIndex(100);
        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 1);

    }

    TEST_F(TrackPluginsViewModelTest, setSelectedPluginIndexZeroPlugin)
    {
        // Multi-Track
        zeroPluginViewModel.setSelectedPluginIndex(-1);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(-2);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(-100);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(0);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(7);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(8);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);
        zeroPluginViewModel.setSelectedPluginIndex(100);
        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), -1);

    }

    TEST_F(TrackPluginsViewModelTest, getSelectedPluginSinglePlugin)
    {

        EXPECT_EQ(singlePluginViewModel.getSelectedPlugin()->getName(), juce::String("Volume & Pan Plugin"));

    }

    TEST_F(TrackPluginsViewModelTest, getSelectedPluginMultiPlugin)
    {

        multiPluginViewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(multiPluginViewModel.getSelectedPlugin()->getName(), juce::String("Level Meter"));

    }

    TEST_F(TrackPluginsViewModelTest, getSelectedPluginZeroPlugin)
    {

        EXPECT_EQ(zeroPluginViewModel.getSelectedPlugin(), nullptr);

    }

    using ::testing::_;
    TEST_F(TrackPluginsViewModelTest, selectedIndexChangesSinglePlugin)
    {

        MockTrackPluginsViewModelListener listener;
        // its called once when the listener is added
        // and once mor the first time the index is set
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(2);

        singlePluginViewModel.addListener(&listener);

        singlePluginViewModel.setSelectedPluginIndex(-10);
        singlePluginViewModel.handleUpdateNowIfNeeded();

        singlePluginViewModel.setSelectedPluginIndex(-1);
        singlePluginViewModel.handleUpdateNowIfNeeded();

        singlePluginViewModel.setSelectedPluginIndex(-100);
        singlePluginViewModel.handleUpdateNowIfNeeded();

        singlePluginViewModel.setSelectedPluginIndex(1);
        singlePluginViewModel.handleUpdateNowIfNeeded();

        singlePluginViewModel.setSelectedPluginIndex(100);
        singlePluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, selectedIndexChangesMultiPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, selectedPluginIndexChanged(1))
                .Times(2);

        // its called once when the listener is added once when the index is set initially, and one more time
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(3);

        multiPluginViewModel.addListener(&listener);

        multiPluginViewModel.setSelectedPluginIndex(1);
        multiPluginViewModel.handleUpdateNowIfNeeded();

        multiPluginViewModel.setSelectedPluginIndex(0);
        multiPluginViewModel.handleUpdateNowIfNeeded();

        multiPluginViewModel.setSelectedPluginIndex(12);
        multiPluginViewModel.handleUpdateNowIfNeeded();

        multiPluginViewModel.setSelectedPluginIndex(-1);
        multiPluginViewModel.handleUpdateNowIfNeeded();

        multiPluginViewModel.setSelectedPluginIndex(-10);
        multiPluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, selectedIndexChangesZeroPlugin)
    {

        MockTrackPluginsViewModelListener listener;

        // should only be called once when the listener is set
        EXPECT_CALL(listener, selectedPluginIndexChanged(-1))
                .Times(1);

        zeroPluginViewModel.addListener(&listener);

        zeroPluginViewModel.setSelectedPluginIndex(3);
        zeroPluginViewModel.handleUpdateNowIfNeeded();

        zeroPluginViewModel.setSelectedPluginIndex(10);
        zeroPluginViewModel.handleUpdateNowIfNeeded();

        zeroPluginViewModel.setSelectedPluginIndex(12);
        zeroPluginViewModel.handleUpdateNowIfNeeded();

        zeroPluginViewModel.setSelectedPluginIndex(-1);
        zeroPluginViewModel.handleUpdateNowIfNeeded();

        zeroPluginViewModel.setSelectedPluginIndex(-10);
        zeroPluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, pluginDeletionChangesSinglePlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listener, selectedPluginIndexChanged(-1))
                .Times(1);

        singlePluginViewModel.addListener(&listener);
        singlePluginViewModel.getSelectedPlugin()->removeFromParent();
        singlePluginViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        singlePluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, lastPluginDeletionChangesMultiPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        EXPECT_CALL(listener, selectedPluginIndexChanged(1))
                .Times(1);

        // selected index should decrease after deleting last plugin
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        multiPluginViewModel.setSelectedPluginIndex(1);
        multiPluginViewModel.handleUpdateNowIfNeeded();

        multiPluginViewModel.addListener(&listener);
        multiPluginViewModel.getSelectedPlugin()->removeFromParent();
        multiPluginViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiPluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, nonEdgePluginDeletionChangesMultiPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // selected index should stay the same after deletion
        // only call is from adding listener
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        multiPluginViewModel.addListener(&listener);
        multiPluginViewModel.getSelectedPlugin()->removeFromParent();
        multiPluginViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiPluginViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(TrackPluginsViewModelTest, pluginAdditionChangesZeroPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(-1))
                .Times(1);

        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        zeroPluginViewModel.addListener(&listener);
        auto track = tracktion_engine::getAudioTracks(*zeroPluginEdit)[0];
        track->pluginList.insertPlugin( tracktion_engine::LevelMeterPlugin::create(), -1);
        zeroPluginViewModel.handleUpdateNowIfNeeded();
        zeroPluginViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(zeroPluginViewModel.getSelectedPluginIndex(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, pluginAdditionChangesSinglePlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        singlePluginViewModel.addListener(&listener);
        auto track = tracktion_engine::getAudioTracks(*singlePluginEdit)[0];
        track->pluginList.insertPlugin( tracktion_engine::LevelMeterPlugin::create(), -1);
        singlePluginViewModel.handleUpdateNowIfNeeded();
        singlePluginViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(singlePluginViewModel.getSelectedPluginIndex(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, pluginAdditionChangesMultiPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        multiPluginViewModel.addListener(&listener);
        auto track = tracktion_engine::getAudioTracks(*multiPluginEdit)[0];
        track->pluginList.insertPlugin( tracktion_engine::LevelMeterPlugin::create(), -1);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        multiPluginViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiPluginViewModel.getSelectedPluginIndex(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, selectionSinglePlugin)
    {

        auto track = tracktion_engine::getAudioTracks(*singlePluginEdit)[0];
        EXPECT_EQ(singlePluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), true);

        singlePluginViewModel.setSelectedPluginIndex(10);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singlePluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), true);

        singlePluginViewModel.setSelectedPluginIndex(-1);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singlePluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), true);

    }

    TEST_F(TrackPluginsViewModelTest, selectionMultiPlugin)
    {
        auto track = tracktion_engine::getAudioTracks(*multiPluginEdit)[0];
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), true);
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(1)), false);

        multiPluginViewModel.setSelectedPluginIndex(10);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(1)), true);
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), false);

        multiPluginViewModel.setSelectedPluginIndex(-3);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), true);
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(1)), false);


        multiPluginViewModel.setSelectedPluginIndex(1);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(1)), true);
        EXPECT_EQ(multiPluginSelectionManager.isSelected(track->pluginList.getPlugins().getObjectPointerUnchecked(0)), false);


    }

    TEST_F(TrackPluginsViewModelTest, selectionZeroPlugin)
    {

        EXPECT_EQ(zeroPluginSelectionManager.getSelectedObjects().size(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, getPluginsZeroPlugin)
    {

        EXPECT_EQ(zeroPluginViewModel.getPluginNames().size(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, getPluginsSinglePlugin)
    {

        EXPECT_EQ(singlePluginViewModel.getPluginNames().size(), 1);

    }

    TEST_F(TrackPluginsViewModelTest, getPluginsMultiPlugin)
    {

        EXPECT_EQ(multiPluginViewModel.getPluginNames().size(), 2);

    }

    TEST_F(TrackPluginsViewModelTest, addingPluginsUpdatesPluginNames)
    {

        int initialSize = multiPluginViewModel.getPluginNames().size();
        auto track = tracktion_engine::getAudioTracks(*multiPluginEdit)[0];
        track->pluginList.insertPlugin( tracktion_engine::LevelMeterPlugin::create(), -1);
        multiPluginViewModel.handleUpdateNowIfNeeded();
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiPluginViewModel.getPluginNames().size(), initialSize + 1);

    }

    TEST_F(TrackPluginsViewModelTest, deletePluginZeroPlugins)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(1);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(-1))
                .Times(1);

        zeroPluginViewModel.addListener(&listener);
        zeroPluginViewModel.deleteSelectedPlugin();
        zeroPluginViewModel.handleUpdateNowIfNeeded();
        zeroPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(zeroPluginViewModel.getPluginNames().size(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, deletePluginSinglePlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listener, selectedPluginIndexChanged(-1))
                .Times(1);

        singlePluginViewModel.addListener(&listener);
        singlePluginViewModel.deleteSelectedPlugin();
        singlePluginViewModel.handleUpdateNowIfNeeded();
        singlePluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singlePluginViewModel.getPluginNames().size(), 0);

    }

    TEST_F(TrackPluginsViewModelTest, deletePluginMultiPlugin)
    {

        MockTrackPluginsViewModelListener listener;
        EXPECT_CALL(listener, pluginsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        multiPluginViewModel.addListener(&listener);
        multiPluginViewModel.deleteSelectedPlugin();
        multiPluginViewModel.handleUpdateNowIfNeeded();
        multiPluginViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiPluginViewModel.getPluginNames().size(), 1);

    }

}