#pragma once
#include "AppLookAndFeel.h"
#include "FontData.h"
#include <juce_gui_extra/juce_gui_extra.h>

class OctaveDisplayComponent : public juce::Component {
  public:
    OctaveDisplayComponent();

    void paint(juce::Graphics &g) override;
    void resized() override;
    void setOctave(int octave);

  private:
    int octaveInt = 0;
    juce::Typeface::Ptr fontAwesomeTypeface =
        juce::Typeface::createSystemTypefaceFor(
            FontData::FontAwesome6FreeSolid900_otf,
            FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(fontAwesomeTypeface);
    AppLookAndFeel appLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OctaveDisplayComponent)
};