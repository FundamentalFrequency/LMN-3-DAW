#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockEditItemListViewModelListener.h"

namespace AppViewModelsTests
{

    class EditItemListViewModelTest : public ::testing::Test {
    protected:

        EditItemListViewModelTest()
                : singleTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  multiTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  zeroTrackEdit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  singleTrackAdapter(*singleTrackEdit),
                  multiTrackAdapter(*multiTrackEdit),
                  zeroTrackAdapter(*zeroTrackEdit),
                  singleTrackSelectionManager(engine),
                  multiTrackSelectionManager(engine),
                  zeroTrackSelectionManager(engine),
                  singleItemViewModel(singleTrackEdit->state, tracktion_engine::IDs::TRACK, singleTrackSelectionManager, &singleTrackAdapter),
                  multiItemViewModel(multiTrackEdit->state, tracktion_engine::IDs::TRACK, multiTrackSelectionManager, &multiTrackAdapter),
                  zeroItemViewModel(zeroTrackEdit->state, tracktion_engine::IDs::TRACK, zeroTrackSelectionManager, &zeroTrackAdapter)
        {}

        void SetUp() override {

            singleItemViewModel.handleUpdateNowIfNeeded();
            multiItemViewModel.handleUpdateNowIfNeeded();
            zeroItemViewModel.handleUpdateNowIfNeeded();

            multiTrackEdit->ensureNumberOfAudioTracks(8);
            multiItemViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after an item gets added
            multiItemViewModel.handleUpdateNowIfNeeded();

            zeroTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*zeroTrackEdit).getUnchecked(0));
            zeroItemViewModel.handleUpdateNowIfNeeded();
            // must handle update a second time since the selected index change gets pushed out
            // in the handleAsyncUpdate after an item gets added
            zeroItemViewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        tracktion_engine::SelectionManager singleTrackSelectionManager;
        tracktion_engine::SelectionManager multiTrackSelectionManager;
        tracktion_engine::SelectionManager zeroTrackSelectionManager;
        std::unique_ptr<tracktion_engine::Edit> singleTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> multiTrackEdit;
        std::unique_ptr<tracktion_engine::Edit> zeroTrackEdit;
        app_view_models::TracksListAdapter singleTrackAdapter;
        app_view_models::TracksListAdapter multiTrackAdapter;
        app_view_models::TracksListAdapter zeroTrackAdapter;
        app_view_models::EditItemListViewModel singleItemViewModel;
        app_view_models::EditItemListViewModel multiItemViewModel;
        app_view_models::EditItemListViewModel zeroItemViewModel;


    };

    TEST_F(EditItemListViewModelTest, initialSelectedItemIndex)
    {

        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0) << "incorrect initial item index for single track edit";
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0) << "incorrect initial item index for multi-track edit";
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1) << "incorrect initial item index for zero-track edit";

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexSingleItem)
    {

        // Single Track
        singleItemViewModel.setSelectedItemIndex(-1);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(-2);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(-100);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(0);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(1);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(2);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

        singleItemViewModel.setSelectedItemIndex(100);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexMultiItem)
    {
        // Multi-Track
        multiItemViewModel.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 7);

        multiItemViewModel.setSelectedItemIndex(-1);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0);

        multiItemViewModel.setSelectedItemIndex(-2);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0);

        multiItemViewModel.setSelectedItemIndex(-100);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0);

        multiItemViewModel.setSelectedItemIndex(0);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0);

        multiItemViewModel.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 7);

        multiItemViewModel.setSelectedItemIndex(8);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 7);

        multiItemViewModel.setSelectedItemIndex(100);
        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 7);

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexZeroItem)
    {

        zeroItemViewModel.setSelectedItemIndex(-1);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(-2);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(-100);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(0);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(7);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(8);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

        zeroItemViewModel.setSelectedItemIndex(100);
        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), -1);

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemSingleItem)
    {

        EXPECT_EQ(singleItemViewModel.getSelectedItem()->getName(), juce::String("Track 1"));

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemMultiItem)
    {

        multiItemViewModel.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.getSelectedItem()->getName(), juce::String("Track 8"));

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemZeroItem)
    {

        EXPECT_EQ(zeroItemViewModel.getSelectedItem(), nullptr);

    }

    using ::testing::_;
    TEST_F(EditItemListViewModelTest, selectedIndexChangesSingleItem)
    {

        MockEditItemListViewModelListener listener;
        // called once when added listener added, once again initial time selected track is set
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(2);

        singleItemViewModel.addListener(&listener);

        singleItemViewModel.setSelectedItemIndex(-10);
        singleItemViewModel.handleUpdateNowIfNeeded();

        singleItemViewModel.setSelectedItemIndex(-1);
        singleItemViewModel.handleUpdateNowIfNeeded();

        singleItemViewModel.setSelectedItemIndex(-100);
        singleItemViewModel.handleUpdateNowIfNeeded();

        singleItemViewModel.setSelectedItemIndex(1);
        singleItemViewModel.handleUpdateNowIfNeeded();

        singleItemViewModel.setSelectedItemIndex(100);
        singleItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, selectedIndexChangesMultiItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, selectedIndexChanged(3))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(7))
                .Times(1);

        // called once when listener added
        // and one more time after
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(2);

        multiItemViewModel.addListener(&listener);

        multiItemViewModel.setSelectedItemIndex(3);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.setSelectedItemIndex(10);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.setSelectedItemIndex(12);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.setSelectedItemIndex(-1);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.setSelectedItemIndex(-10);
        multiItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, selectedIndexChangesZeroItem) {

        MockEditItemListViewModelListener listener;

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(-1))
                .Times(1);

        zeroItemViewModel.addListener(&listener);

        zeroItemViewModel.setSelectedItemIndex(3);
        zeroItemViewModel.handleUpdateNowIfNeeded();

        zeroItemViewModel.setSelectedItemIndex(10);
        zeroItemViewModel.handleUpdateNowIfNeeded();

        zeroItemViewModel.setSelectedItemIndex(12);
        zeroItemViewModel.handleUpdateNowIfNeeded();

        zeroItemViewModel.setSelectedItemIndex(-1);
        zeroItemViewModel.handleUpdateNowIfNeeded();

        zeroItemViewModel.setSelectedItemIndex(-10);
        zeroItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, itemDeletionChangesSingleItem)
    {

        MockEditItemListViewModelListener listener;

        // called once when listener is added and again when track gets deleted
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(-1))
                .Times(1);

        singleItemViewModel.addListener(&listener);
        singleTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*singleTrackEdit)[0]);
        singleItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        singleItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, lastItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(7))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(6))
                .Times(1);

        multiItemViewModel.setSelectedItemIndex(7);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(7));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, nonEdgeItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called once when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(3))
                .Times(1);

        multiItemViewModel.setSelectedItemIndex(3);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(3));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, firstItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        multiItemViewModel.setSelectedItemIndex(0);
        multiItemViewModel.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&listener);
        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(0));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesZeroItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(-1))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        zeroItemViewModel.addListener(&listener);
        zeroTrackEdit->ensureNumberOfAudioTracks(1);
        zeroItemViewModel.handleUpdateNowIfNeeded();
        zeroItemViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(zeroItemViewModel.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesSingleItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        singleItemViewModel.addListener(&listener);
        singleTrackEdit->ensureNumberOfAudioTracks(4);
        singleItemViewModel.handleUpdateNowIfNeeded();
        singleItemViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(singleItemViewModel.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesMultiItem)
    {

        MockEditItemListViewModelListener listener;
        EXPECT_CALL(listener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(1);

        multiItemViewModel.addListener(&listener);
        multiTrackEdit->ensureNumberOfAudioTracks(16);
        multiItemViewModel.handleUpdateNowIfNeeded();
        multiItemViewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiItemViewModel.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, selectionSingleItem)
    {

        auto track = tracktion_engine::getAudioTracks(*singleTrackEdit)[0];
        EXPECT_EQ(singleTrackSelectionManager.isSelected(track), true);

        singleItemViewModel.setSelectedItemIndex(10);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackSelectionManager.isSelected(track), true);

        singleItemViewModel.setSelectedItemIndex(-10);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleTrackSelectionManager.isSelected(track), true);

    }

    TEST_F(EditItemListViewModelTest, selectionMultiItem)
    {
        auto track = tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(0);
        EXPECT_EQ(multiTrackSelectionManager.isSelected(track), true);

        multiItemViewModel.setSelectedItemIndex(100);
        multiItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackSelectionManager.isSelected(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(7)), true);

        multiItemViewModel.setSelectedItemIndex(-3);
        multiItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackSelectionManager.isSelected(track), true);

        multiItemViewModel.setSelectedItemIndex(7);
        multiItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(multiTrackSelectionManager.isSelected(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(7)), true);

    }

    TEST_F(EditItemListViewModelTest, selectionZeroItem)
    {

        EXPECT_EQ(zeroTrackSelectionManager.getSelectedObjects().size(), 0);

    }


}