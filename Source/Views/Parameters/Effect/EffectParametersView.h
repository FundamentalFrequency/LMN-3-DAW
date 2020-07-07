#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "EffectParameters.h"
class EffectParametersView : public juce::Component 
{
public:
    EffectParametersView(EffectParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void setParameters(EffectParameters* params);
    
private:
    EffectParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectParametersView)
};

