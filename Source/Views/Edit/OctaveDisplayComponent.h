#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "AppLookAndFeel.h"

class OctaveDisplayComponent : public juce::Component
{
public:
    OctaveDisplayComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void setOctave(int octave);

private:
    int octaveInt = 0;
    AppLookAndFeel appLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OctaveDisplayComponent)
};

