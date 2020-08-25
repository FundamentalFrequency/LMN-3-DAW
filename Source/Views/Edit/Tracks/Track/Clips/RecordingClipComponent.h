#pragma once
#include <tracktion_engine/tracktion_engine.h>
class RecordingClipComponent
: public juce::Component,
  private juce::Timer
{

public:

    RecordingClipComponent(tracktion_engine::Track::Ptr t);
    void paint(juce::Graphics& g) override;

private:

    void timerCallback() override;
    void updatePosition();

    tracktion_engine::Track::Ptr track;
    double punchInTime = -1.0;
};

