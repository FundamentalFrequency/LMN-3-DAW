#pragma once
#include "AppLookAndFeel.h"
#include <juce_gui_basics/juce_gui_basics.h>
class SelectedTrackMarker : public juce::Component {

  public:
    void paint(juce::Graphics &g) override;

  private:
    AppLookAndFeel appLookAndFeel;
};
