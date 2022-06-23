#pragma once
#include <app_view_models/app_view_models.h>
#include <gmock/gmock.h>

class MockTrackViewModelListener
    : public app_view_models::TrackViewModel::Listener {
  public:
    MOCK_METHOD(void, clipsChanged,
                (const juce::Array<tracktion::Clip *> &clips),
                (override));
    MOCK_METHOD(void, clipPositionsChanged,
                (const juce::Array<tracktion::Clip *> &clips),
                (override));
    MOCK_METHOD(void, transportChanged, (), (override));
};