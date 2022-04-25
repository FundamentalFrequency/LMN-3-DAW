#pragma once
#include "FontData.h"
#include "LabelColour1LookAndFeel.h"
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class ListTitle : public juce::Component {

  public:
    enum class IconType {
        FONT_AWESOME = 0,
        NONE = 1

    };

    ListTitle(const juce::String &titleString, IconType type,
              const juce::String &iconString);
    ~ListTitle();

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Typeface::Ptr fontAwesomeTypeface =
        juce::Typeface::createSystemTypefaceFor(
            FontData::FontAwesome6FreeSolid900_otf,
            FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(fontAwesomeTypeface);

    juce::String title;
    IconType iconType;
    juce::String icon;
    juce::Label titleLabel;
    juce::Label iconLabel;

    LabelColour1LookAndFeel labelColour1LookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ListTitle)
};
