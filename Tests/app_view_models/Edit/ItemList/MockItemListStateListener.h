#pragma once
#include <app_view_models/app_view_models.h>
#include <gmock/gmock.h>

class MockItemListStateListener
    : public app_view_models::ItemListState::Listener {
  public:
    MOCK_METHOD(void, selectedIndexChanged, (int newIndex), (override));
};
