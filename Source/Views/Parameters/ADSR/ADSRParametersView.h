#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "ADSRParameters.h"
#include "PresetSlots.h"

class ADSRParametersView
    : public juce::Component,
      public PresetSlots::Listener
{
public:
    ADSRParametersView(ADSRParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;
    void setParameters(ADSRParameters* params);

    void currentPresetADSRParametersChanged(ADSRParameters* params) override;
    
private:
    ADSRParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRParametersView)
};

