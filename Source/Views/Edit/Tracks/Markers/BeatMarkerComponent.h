#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
class BeatMarkerComponent : public juce::Component
{

public:

    BeatMarkerComponent();
    void paint(juce::Graphics& g) override;
    juce::Colour markerColour = juce::Colours::grey;

};


