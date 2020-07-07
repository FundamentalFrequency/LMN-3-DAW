#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "ADSRParameters.h"

class ADSRParametersView : public juce::Component 
{
public:
    ADSRParametersView(ADSRParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;
    void setParameters(ADSRParameters* params);
    
private:
    ADSRParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRParametersView)
};

