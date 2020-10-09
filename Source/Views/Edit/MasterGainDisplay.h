#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "AppLookAndFeel.h"

class MasterGainDisplay : public juce::Component
{
public:
    MasterGainDisplay();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void setGain(int gain);

private:
    int gain = 0;
    AppLookAndFeel appLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterGainDisplay)
};

