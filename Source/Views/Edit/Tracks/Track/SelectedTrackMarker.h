#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "AppLookAndFeel.h"
class SelectedTrackMarker : public juce::Component
{

public:

    void paint(juce::Graphics& g) override;

private:

    AppLookAndFeel appLookAndFeel;
};



