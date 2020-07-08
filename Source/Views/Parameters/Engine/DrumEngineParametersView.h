#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "EngineKnobsView.h"
#include "EngineParameters.h"
#include "PresetSlots.h"

class DrumEngineParametersView
    : public juce::Component,
      public PresetSlots::Listener
{
public:
    DrumEngineParametersView(EngineParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void currentPresetEngineParametersChanged(EngineParameters* params) override;

private:
    EngineParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumEngineParametersView)
};

