#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <fontaudio/fontaudio.h>
#include <FontData.h>
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

private:

    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;

    // Font awesome typeface for play button since fontaudio does not have filled icons
    Typeface::Ptr faTypeface = juce::Typeface::createSystemTypefaceFor(FontData::FontAwesome5FreeSolid900_otf, FontData::FontAwesome5FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(faTypeface);

    juce::String playIcon = juce::String::charToString(0xf04b);
    fontaudio::IconName recordIcon = fontaudio::Armrecording;

    juce::Label playingLabel;
    juce::Label recordingLabel;
    juce::Label timecodeLabel;
    juce::Label trackNumberLabel;
    LabelColour1LookAndFeel labelColour1LookAndFeel;
    AppLookAndFeel appLookAndFeel;

};



