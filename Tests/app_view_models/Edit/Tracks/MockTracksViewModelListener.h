#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockTracksViewModelListener : public app_view_models::TracksViewModel::Listener
{
public:
    MOCK_METHOD(void, selectedTrackIndexChanged, (int newIndex), (override));
    MOCK_METHOD(void, tracksChanged, (), (override));
};

