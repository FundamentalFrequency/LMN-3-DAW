#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockEditItemListViewModelListener.h"
#include "MockItemListStateListener.h"

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
                  singleItemViewModel(singleTrackEdit->state, singleTrackEdit->state, tracktion_engine::IDs::TRACK, singleTrackSelectionManager, &singleTrackAdapter),
                  multiItemViewModel(multiTrackEdit->state, multiTrackEdit->state, tracktion_engine::IDs::TRACK, multiTrackSelectionManager, &multiTrackAdapter),
                  zeroItemViewModel(zeroTrackEdit->state, zeroTrackEdit->state, tracktion_engine::IDs::TRACK, zeroTrackSelectionManager, &zeroTrackAdapter)
        {}

        void SetUp() override {

            singleItemViewModel.handleUpdateNowIfNeeded();
            singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

            multiItemViewModel.handleUpdateNowIfNeeded();
            multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

            zeroItemViewModel.handleUpdateNowIfNeeded();
            zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

            multiTrackEdit->ensureNumberOfAudioTracks(8);
            multiItemViewModel.handleUpdateNowIfNeeded();
            multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

            zeroTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*zeroTrackEdit)[0]);
            zeroItemViewModel.handleUpdateNowIfNeeded();
            zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

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

        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0) << "incorrect initial item index for single track edit";
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0) << "incorrect initial item index for multi-track edit";
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1) << "incorrect initial item index for zero-track edit";

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexSingleItem)
    {

        // Single Track
        singleItemViewModel.itemListState.setSelectedItemIndex(-1);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(-2);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(-100);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(0);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(1);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(2);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

        singleItemViewModel.itemListState.setSelectedItemIndex(100);
        singleItemViewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexMultiItem)
    {
        // Multi-Track
        multiItemViewModel.itemListState.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 7);

        multiItemViewModel.itemListState.setSelectedItemIndex(-1);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0);

        multiItemViewModel.itemListState.setSelectedItemIndex(-2);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0);

        multiItemViewModel.itemListState.setSelectedItemIndex(-100);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0);

        multiItemViewModel.itemListState.setSelectedItemIndex(0);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0);

        multiItemViewModel.itemListState.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 7);

        multiItemViewModel.itemListState.setSelectedItemIndex(8);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 7);

        multiItemViewModel.itemListState.setSelectedItemIndex(100);
        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 7);

    }

    TEST_F(EditItemListViewModelTest, setSelectedItemIndexZeroItem)
    {

        zeroItemViewModel.itemListState.setSelectedItemIndex(-1);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(-2);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(-100);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(0);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(7);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(8);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

        zeroItemViewModel.itemListState.setSelectedItemIndex(100);
        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), -1);

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemSingleItem)
    {

        EXPECT_EQ(singleItemViewModel.getSelectedItem()->getName(), juce::String("Track 1"));

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemMultiItem)
    {

        multiItemViewModel.itemListState.setSelectedItemIndex(7);
        EXPECT_EQ(multiItemViewModel.getSelectedItem()->getName(), juce::String("Track 8"));

    }

    TEST_F(EditItemListViewModelTest, getSelectedItemZeroItem)
    {

        EXPECT_EQ(zeroItemViewModel.getSelectedItem(), nullptr);

    }

    using ::testing::_;
    TEST_F(EditItemListViewModelTest, selectedIndexChangesSingleItem)
    {

        MockItemListStateListener listener;

        // called once when added listener added, once again initial time selected track is set
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(2);

        singleItemViewModel.itemListState.addListener(&listener);

        singleItemViewModel.itemListState.setSelectedItemIndex(-10);
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

        singleItemViewModel.itemListState.setSelectedItemIndex(-1);
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

        singleItemViewModel.itemListState.setSelectedItemIndex(-100);
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

        singleItemViewModel.itemListState.setSelectedItemIndex(1);
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

        singleItemViewModel.itemListState.setSelectedItemIndex(100);
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, selectedIndexChangesMultiItem)
    {

        MockItemListStateListener listener;
        EXPECT_CALL(listener, selectedIndexChanged(3))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(7))
                .Times(1);

        // called once when listener added
        // and one more time after
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(2);

        multiItemViewModel.itemListState.addListener(&listener);

        multiItemViewModel.itemListState.setSelectedItemIndex(3);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.itemListState.setSelectedItemIndex(10);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.itemListState.setSelectedItemIndex(12);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.itemListState.setSelectedItemIndex(-1);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.itemListState.setSelectedItemIndex(-10);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, selectedIndexChangesZeroItem) {

        MockItemListStateListener listener;

        // called when listener is added
        EXPECT_CALL(listener, selectedIndexChanged(-1))
                .Times(1);

        zeroItemViewModel.itemListState.addListener(&listener);

        zeroItemViewModel.itemListState.setSelectedItemIndex(3);
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

        zeroItemViewModel.itemListState.setSelectedItemIndex(10);
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

        zeroItemViewModel.itemListState.setSelectedItemIndex(12);
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

        zeroItemViewModel.itemListState.setSelectedItemIndex(-1);
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

        zeroItemViewModel.itemListState.setSelectedItemIndex(-10);
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, itemDeletionChangesSingleItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        // called once when listener is added and again when track gets deleted
        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(0))
                .Times(1);

        EXPECT_CALL(itemListStateListener, selectedIndexChanged(-1))
                .Times(1);

        singleItemViewModel.addListener(&editItemListViewModelListener);
        singleItemViewModel.itemListState.addListener(&itemListStateListener);

        singleTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*singleTrackEdit)[0]);
        singleItemViewModel.handleUpdateNowIfNeeded();
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, lastItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(7))
                .Times(1);

        EXPECT_CALL(itemListStateListener, selectedIndexChanged(6))
                .Times(1);

        multiItemViewModel.itemListState.setSelectedItemIndex(7);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&editItemListViewModelListener);
        multiItemViewModel.itemListState.addListener(&itemListStateListener);

        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(7));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, nonEdgeItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called once when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(3))
                .Times(1);

        multiItemViewModel.itemListState.setSelectedItemIndex(3);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&editItemListViewModelListener);
        multiItemViewModel.itemListState.addListener(&itemListStateListener);

        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(3));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, firstItemDeletionChangesMultiItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(0))
                .Times(1);

        multiItemViewModel.itemListState.setSelectedItemIndex(0);
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        multiItemViewModel.addListener(&editItemListViewModelListener);
        multiItemViewModel.itemListState.addListener(&itemListStateListener);

        multiTrackEdit->deleteTrack(tracktion_engine::getAudioTracks(*multiTrackEdit).getUnchecked(0));
        multiItemViewModel.handleUpdateNowIfNeeded();
        // must handle update a second time since the selected index change gets pushed out
        // in the handleAsyncUpdate after a track gets deleted
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesZeroItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(-1))
                .Times(1);

        EXPECT_CALL(itemListStateListener, selectedIndexChanged(0))
                .Times(1);

        zeroItemViewModel.addListener(&editItemListViewModelListener);
        zeroItemViewModel.itemListState.addListener(&itemListStateListener);

        zeroTrackEdit->ensureNumberOfAudioTracks(1);
        zeroItemViewModel.handleUpdateNowIfNeeded();
        zeroItemViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(zeroItemViewModel.itemListState.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesSingleItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(0))
                .Times(1);

        singleItemViewModel.addListener(&editItemListViewModelListener);
        singleItemViewModel.itemListState.addListener(&itemListStateListener);

        singleTrackEdit->ensureNumberOfAudioTracks(4);
        singleItemViewModel.handleUpdateNowIfNeeded();
        singleItemViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(singleItemViewModel.itemListState.getSelectedItemIndex(), 0);

    }

    TEST_F(EditItemListViewModelTest, itemAdditionChangesMultiItem)
    {

        MockEditItemListViewModelListener editItemListViewModelListener;
        MockItemListStateListener itemListStateListener;

        EXPECT_CALL(editItemListViewModelListener, itemsChanged())
                .Times(2);

        // called when listener is added
        EXPECT_CALL(itemListStateListener, selectedIndexChanged(0))
                .Times(1);

        multiItemViewModel.addListener(&editItemListViewModelListener);
        multiItemViewModel.itemListState.addListener(&itemListStateListener);

        multiTrackEdit->ensureNumberOfAudioTracks(16);
        multiItemViewModel.handleUpdateNowIfNeeded();
        multiItemViewModel.itemListState.handleUpdateNowIfNeeded();

        EXPECT_EQ(multiItemViewModel.itemListState.getSelectedItemIndex(), 0);

    }


}