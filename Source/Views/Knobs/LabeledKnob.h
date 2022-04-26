#pragma once
#include "AppLookAndFeel.h"
#include <app_services/app_services.h>
#include <juce_gui_basics/juce_gui_basics.h>
constexpr float sliderHeight = 0.8f;
constexpr float labelHeight = 1.f - sliderHeight;

class LabeledKnob : public juce::Component {
  public:
    LabeledKnob();

    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Slider &getSlider();
    juce::Label &getLabel();

  private:
    juce::Slider knob;
    juce::Label label;
    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabeledKnob)
};
