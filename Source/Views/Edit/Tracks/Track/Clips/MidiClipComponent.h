#pragma once
#include "ClipComponent.h"
#include <tracktion_engine/tracktion_engine.h>
class MidiClipComponent : public ClipComponent {
  public:
    MidiClipComponent(tracktion::Clip::Ptr c,
                      app_services::TimelineCamera &camera);

    tracktion::MidiClip *getMidiClip();

    void paint(juce::Graphics &g) override;
};
