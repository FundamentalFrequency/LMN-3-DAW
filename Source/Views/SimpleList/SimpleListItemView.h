#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class SimpleListItemView : public juce::Component
{

public:
    explicit SimpleListItemView(juce::String title);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setTitle(juce::String t);
    void setSelected(bool selected);

private:
    juce::Label titleLabel;
    juce::Colour backgroundColour;
    juce::Colour textColour;
    bool isSelected = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleListItemView)

};


