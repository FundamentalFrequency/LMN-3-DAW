#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "EngineParameters.h"
#include "KnobControlledParameters.h"
#include "PresetSlots.h"
class KnobsView
    : public juce::Component,
      public juce::Slider::Listener,
      public juce::ChangeListener,
      public PresetSlots::Listener
{
public:
    KnobsView(KnobControlledParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void enableKnobs();
    void disableKnobs();

    void sliderValueChanged(juce::Slider* slider);
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void currentPresetParametersChanged(KnobControlledParameters* params) override;

    void setParameters(KnobControlledParameters* params);


private:

    KnobControlledParameters* parameters;

    juce::Slider knob1;
    juce::Slider knob2;
    juce::Slider knob3;
    juce::Slider knob4;

    juce::FlexBox fb;

    void flexboxSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobsView)
};

