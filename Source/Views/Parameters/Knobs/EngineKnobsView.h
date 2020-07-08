#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "EngineParameters.h"

class EngineKnobsView
    : public juce::Component,
      public EngineParameters::Listener
{
public:
    EngineKnobsView(EngineParameters* params);

    juce::Slider knob1;
    juce::Slider knob2;
    juce::Slider knob3;
    juce::Slider knob4;

    void paint(juce::Graphics&) override;
    void resized() override;

    void parameter1Changed(double newValue) override;
    void parameter2Changed(double newValue) override;
    void parameter3Changed(double newValue) override;
    void parameter4Changed(double newValue) override;


    
private:

    EngineParameters* parameters;
    juce::FlexBox fb;

    void flexboxSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EngineKnobsView)
};

