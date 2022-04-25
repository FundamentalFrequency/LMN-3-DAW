#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "AppLookAndFeel.h"

class PlayheadComponent
    : public juce::Component
{

public:

    PlayheadComponent();
    void paint(juce::Graphics& g) override;

private:

    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayheadComponent)

};


