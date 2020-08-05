#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
class ListRow : public juce::Component
{
public:

    explicit ListRow(const juce::String& title);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setTitle(const juce::String& t);
    void setSelected(bool selected);
    void setSelectedBackgroundColour(juce::Colour selectedBackgroundColour);

private:

    juce::Label titleLabel;
    juce::Colour selectedBackgroundColour;
    bool isSelected = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ListRow)
};


