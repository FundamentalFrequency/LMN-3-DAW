#pragma once
#include "AppLookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>

class LoopMarkerComponent : public juce::Component {

  public:
    LoopMarkerComponent() = default;
    void paint(juce::Graphics &g) override;

  private:
    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoopMarkerComponent)
};
