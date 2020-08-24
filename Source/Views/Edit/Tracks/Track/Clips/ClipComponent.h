#pragma once
#include <tracktion_engine/tracktion_engine.h>

class ClipComponent : public juce::Component {

public:
    ClipComponent(tracktion_engine::Clip::Ptr c);

    void paint(juce::Graphics& g) override;

    tracktion_engine::Clip& getClip();

protected:
    tracktion_engine::Clip::Ptr clip;

};


