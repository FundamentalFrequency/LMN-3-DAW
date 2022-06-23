#pragma once
#include "AppLookAndFeel.h"
#include <app_services/app_services.h>
#include <tracktion_engine/tracktion_engine.h>

class RecordingClipComponent : public juce::Component, private juce::Timer {
  public:
    RecordingClipComponent(tracktion::Track::Ptr t,
                           app_services::TimelineCamera &cam);
    void paint(juce::Graphics &g) override;

  private:
    tracktion::Track::Ptr track;
    app_services::TimelineCamera &camera;
    double punchInTime = -1.0;

    AppLookAndFeel appLookAndFeel;

    void timerCallback() override;
    void updatePosition();
};
