#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "AppLookAndFeel.h"
#include <fontaudio/fontaudio.h>

class OctaveDisplayComponent : public juce::Component
{
public:
    OctaveDisplayComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void setOctave(int octave);

private:
    int octaveInt = 0;
    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
    fontaudio::IconName keyboardIcon = fontaudio::Keyboard;
    AppLookAndFeel appLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OctaveDisplayComponent)
};

