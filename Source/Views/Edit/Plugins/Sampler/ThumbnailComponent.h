#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class ThumbnailComponent
    : public juce::Component,
      public juce::ChangeListener
{

public:

    ThumbnailComponent(juce::AudioThumbnail& thumb, juce::Colour c);
    ~ThumbnailComponent();
    void paint(juce::Graphics &g) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void setPaintBounds(juce::Rectangle<int> bounds);

private:

    juce::Colour colour;
    juce::AudioThumbnail& thumbnail;
    juce::Rectangle<int> paintBounds = juce::Rectangle<int>(0, 0, 0, 0);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThumbnailComponent);

};

