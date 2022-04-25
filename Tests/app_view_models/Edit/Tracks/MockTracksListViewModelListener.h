#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockTracksListViewModelListener : public app_view_models::TracksListViewModel::Listener
{
public:

    MOCK_METHOD(void, isRecordingChanged, (bool isRecording), (override));
    MOCK_METHOD(void, isPlayingChanged, (bool isPlaying), (override));
    MOCK_METHOD(void, tracksViewTypeChanged, (app_view_models::TracksListViewModel::TracksViewType type), (override));

};

