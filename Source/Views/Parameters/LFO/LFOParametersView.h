#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "LFOParameters.h"
#include "PresetSlots.h"

class LFOParametersView
    : public juce::Component,
      public PresetSlots::Listener
{
public:
    LFOParametersView(LFOParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void currentPresetLFOParametersChanged(LFOParameters* params) override;
    
private:
    LFOParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOParametersView)
};

