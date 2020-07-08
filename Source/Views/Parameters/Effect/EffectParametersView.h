#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "EffectParameters.h"
#include "PresetSlots.h"

class EffectParametersView
    : public juce::Component,
      public PresetSlots::Listener
{
public:
    EffectParametersView(EffectParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void currentPresetEffectParametersChanged(EffectParameters* params) override;
    
private:
    EffectParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectParametersView)
};

