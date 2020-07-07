#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/KnobsView.h"

class EffectParametersView : public juce::Component 
{
public:
    EffectParametersView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Label titleLabel;
    KnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectParametersView)
};

