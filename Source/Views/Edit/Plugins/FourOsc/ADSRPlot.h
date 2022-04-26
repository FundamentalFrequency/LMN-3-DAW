#pragma once
#include "AppLookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>

class ADSRPlot : public juce::Component {
  public:
    ADSRPlot() = default;

    void paint(juce::Graphics &g) override;
    void resized() override;

    float attackValue = 0.0;
    float decayValue = 0.0;
    float sustainValue = 0.0;
    float releaseValue = 0.0;

    AppLookAndFeel appLookAndFeel;
};
