#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockItemListStateListener.h"

namespace AppViewModelsTests {

    class ItemListStateTest : public ::testing::Test {
    protected:

        ItemListStateTest()
                : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  itemListState(edit->state, 8) {}

        void SetUp() override {

            // flush any updates
            itemListState.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::ItemListState itemListState;

    };

    TEST_F(ItemListStateTest, initialItemIndex)
    {

        EXPECT_EQ(itemListState.getSelectedItemIndex(), 0);

    }

    TEST_F(ItemListStateTest, setSelectedItemIndex)
    {

        EXPECT_EQ(itemListState.getSelectedItemIndex(), 0);

        itemListState.setSelectedItemIndex(-1);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 0);
        itemListState.setSelectedItemIndex(-2);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 0);
        itemListState.setSelectedItemIndex(-100);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 0);

        itemListState.setSelectedItemIndex(1);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 1);
        itemListState.setSelectedItemIndex(3);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 3);
        itemListState.setSelectedItemIndex(7);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 7);

        itemListState.setSelectedItemIndex(8);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 7);
        itemListState.setSelectedItemIndex(9);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 7);

        itemListState.setSelectedItemIndex(100);
        EXPECT_EQ(itemListState.getSelectedItemIndex(), 7);

    }

    TEST_F(ItemListStateTest, selectedIndexChanges)
    {

        MockItemListStateListener listener;

        // called when listener is added
        // this is also called the first time the negative index is set
        // since the value tree is using a default value at that point
        EXPECT_CALL(listener, selectedIndexChanged(0))
                .Times(2);

        EXPECT_CALL(listener, selectedIndexChanged(3))
                .Times(1);

        EXPECT_CALL(listener, selectedIndexChanged(7))
                .Times(1);

        itemListState.addListener(&listener);

        itemListState.setSelectedItemIndex(-1);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(-5);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(3);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(7);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(8);
        itemListState.handleUpdateNowIfNeeded();

    }

    using ::testing::_;
    TEST_F(ItemListStateTest, removeListener)
    {

        MockItemListStateListener listener;

        // called when listener is added
        // then again when we set the index manually
        EXPECT_CALL(listener, selectedIndexChanged(_))
                .Times(2);

        itemListState.addListener(&listener);

        itemListState.setSelectedItemIndex(3);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.removeListener(&listener);

        itemListState.setSelectedItemIndex(-5);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(3);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(7);
        itemListState.handleUpdateNowIfNeeded();

        itemListState.setSelectedItemIndex(8);
        itemListState.handleUpdateNowIfNeeded();

    }


}

