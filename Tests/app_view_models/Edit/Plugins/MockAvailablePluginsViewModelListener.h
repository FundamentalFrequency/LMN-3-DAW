#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockAvailablePluginsViewModelListener : public app_view_models::AvailablePluginsViewModel::Listener
{
public:
    MOCK_METHOD(void, selectedPluginIndexChanged, (int newIndex), (override));
    MOCK_METHOD(void, selectedCategoryIndexChanged, (int newIndex), (override));
};

