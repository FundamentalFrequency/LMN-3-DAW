#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>

class TrackView : public juce::Component
{
public:

    enum ColourIds
    {
        unselectedBackgroundColourId = 0x4000680,
        selectedBackgroundColourId = 0x4000681,
        selectedTextColourId = 0x4000682,
        unselectedTextColourId = 0x4000683
    };

    explicit TrackView(juce::String title);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setTitle(juce::String t);
    void setSelected(bool selected);

    void lookAndFeelChanged() override;

private:

    juce::Label titleLabel;
    juce::Colour backgroundColour;
    juce::Colour textColour;
    bool isSelected = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackView)
};

