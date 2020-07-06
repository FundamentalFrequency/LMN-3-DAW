#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "KnobsView.h"

class LFOParametersView : public juce::Component 
{
public:
    LFOParametersView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Label titleLabel;
    KnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOParametersView)
};

