#include <juce_gui_extra/juce_gui_extra.h>

class InstrumentListRow : public juce::Component
{
public:

    enum ColourIds
    {
        unselectedBackgroundColourId = 0x1001280,
        selectedBackgroundColourId = 0x1001281,
        selectedTextColourId = 0x1001282,
        unselectedTextColourId = 0x1001283
    };

    explicit InstrumentListRow(juce::String title);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setTitle(juce::String t);
    void setSelected(bool selected);

private:

    juce::Label titleLabel;
    juce::Colour backgroundColour;
    juce::Colour textColour;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentListRow)
};

