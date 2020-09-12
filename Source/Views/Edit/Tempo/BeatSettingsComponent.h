#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "LabelColour1LookAndFeel.h"
class BeatSettingsComponent
    : public juce::Component
{

public:

    BeatSettingsComponent();
    ~BeatSettingsComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setBpm(double bpm);
    void setBps(double bps);


private:


    juce::Label bpmLabel;
    juce::Label currentBpmValueLabel;

    juce::Label bpsLabel;
    juce::Label currentBpsValueLabel;

    LabelColour1LookAndFeel labelColour1LookAndFeel;

};


