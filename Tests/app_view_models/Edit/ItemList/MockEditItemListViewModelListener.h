#pragma once
#include <app_view_models/app_view_models.h>
#include <gmock/gmock.h>

class MockEditItemListViewModelListener
    : public app_view_models::EditItemListViewModel::Listener {
  public:
    MOCK_METHOD(void, itemsChanged, (), (override));
};
