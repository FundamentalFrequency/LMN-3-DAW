#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/EngineKnobsView.h"
#include "EngineParameters.h"

class DrumEngineParametersView : public juce::Component 
{
public:
    DrumEngineParametersView(EngineParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void refresh();

    void setParameters(EngineParameters* params);

private:
    EngineParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumEngineParametersView)
};

