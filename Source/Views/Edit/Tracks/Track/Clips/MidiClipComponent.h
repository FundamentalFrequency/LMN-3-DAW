#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include "ClipComponent.h"
class MidiClipComponent : public ClipComponent
{

public:

    MidiClipComponent(tracktion_engine::Clip::Ptr c);

    tracktion_engine::MidiClip* getMidiClip();

    void paint(juce::Graphics& g) override;

};


