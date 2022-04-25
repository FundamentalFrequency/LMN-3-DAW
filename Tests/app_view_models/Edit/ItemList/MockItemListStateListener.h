#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockItemListStateListener : public app_view_models::ItemListState::Listener
{
public:

    MOCK_METHOD(void, selectedIndexChanged, (int newIndex), (override));

};

