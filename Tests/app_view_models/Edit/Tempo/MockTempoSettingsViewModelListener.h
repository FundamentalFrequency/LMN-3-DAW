#pragma once
#include <app_view_models/app_view_models.h>
#include <gmock/gmock.h>

class MockTempoSettingsViewModelListener
    : public app_view_models::TempoSettingsViewModel::Listener {
  public:
    MOCK_METHOD(void, bpmChanged, (const double newBpm, const double newBps),
                (override));
    MOCK_METHOD(void, clickTrackGainChanged, (const double newGain),
                (override));
};
