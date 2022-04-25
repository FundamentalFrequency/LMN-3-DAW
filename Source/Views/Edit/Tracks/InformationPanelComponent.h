#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <FontData.h>
#include <juce_graphics/juce_graphics.h>
#include "LabelColour1LookAndFeel.h"
#include "AppLookAndFeel.h"

class InformationPanelComponent
    : public juce::Component
{

public:

    InformationPanelComponent();
    ~InformationPanelComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    void setIsPlaying(bool isPlaying);
    void setIsRecording(bool isRecording);
    void setTimecode(juce::String timecode);
    void setTrackNumber(juce::String trackNumber);
    void setIsLooping(bool isLooping);
    void setIsSoloed(bool solo);
    void setIsMuted(bool muted);

private:
    juce::Typeface::Ptr faTypeface = juce::Typeface::createSystemTypefaceFor(FontData::FontAwesome6FreeSolid900_otf, FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(faTypeface);

    juce::Label timecodeLabel;
    juce::Label trackNumberLabel;
    juce::Label loopingLabel;
    juce::Label soloLabel;
    juce::Label muteLabel;
    LabelColour1LookAndFeel labelColour1LookAndFeel;
    AppLookAndFeel appLookAndFeel;

};



