#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "AppLookAndFeel.h"

class ProgressView: public juce::Component {
public:

    ProgressView();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    AppLookAndFeel appLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProgressView)
};

