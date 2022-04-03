#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "AppLookAndFeel.h"
#include "SVGImageComponent.h"

class ProgressView: public juce::Component, private juce::Timer {
public:
    ProgressView();
    void resized() override;
private:
    AppLookAndFeel appLookAndFeel;
    SVGImageComponent svgImageComponent;
    int refreshRate = 30;
    void timerCallback() override;

    static void setRotatedWithBounds(Component& component, float angle, bool clockWiseRotation, juce::Rectangle<int> bounds);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProgressView)
};

