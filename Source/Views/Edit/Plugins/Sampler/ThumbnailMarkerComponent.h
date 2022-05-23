#pragma once
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
class ThumbnailMarkerComponent : public juce::Component {
  public:
    ThumbnailMarkerComponent(juce::Colour c);
    void paint(juce::Graphics &g) override;

  private:
    juce::Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThumbnailMarkerComponent)
};
