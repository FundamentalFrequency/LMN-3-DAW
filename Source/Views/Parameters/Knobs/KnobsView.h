#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>

class KnobsView
    : public juce::Component,
      public juce::Slider::Listener,
      public juce::ChangeListener,
      public app_models::PresetSlots::Listener
{
public:
    KnobsView(app_models::KnobControlledParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    void enableKnobs();
    void disableKnobs();

    void sliderValueChanged(juce::Slider* slider);
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void currentPresetParametersChanged(app_models::KnobControlledParameters* params) override;

    void setParameters(app_models::KnobControlledParameters* params);


private:

    app_models::KnobControlledParameters* parameters;

    juce::Slider knob1;
    juce::Slider knob2;
    juce::Slider knob3;
    juce::Slider knob4;

    juce::FlexBox fb;

    void flexboxSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobsView)
};

