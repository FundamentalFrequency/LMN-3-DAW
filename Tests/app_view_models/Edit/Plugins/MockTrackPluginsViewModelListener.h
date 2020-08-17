#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockTrackPluginsViewModelListener : public app_view_models::TrackPluginsViewModel::Listener
{
public:
    MOCK_METHOD(void, selectedPluginIndexChanged, (int newIndex), (override));
    MOCK_METHOD(void, pluginsChanged, (), (override));
};

