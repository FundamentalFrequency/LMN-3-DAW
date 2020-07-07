#pragma once
#include <juce_gui_extra/juce_gui_extra.h>


class EngineKnobsView : public juce::Component
{
public:
    EngineKnobsView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:

    juce::Slider knob1;
    juce::Slider knob2;
    juce::Slider knob3;
    juce::Slider knob4;

    juce::FlexBox fb;

    void flexboxSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EngineKnobsView)
};

