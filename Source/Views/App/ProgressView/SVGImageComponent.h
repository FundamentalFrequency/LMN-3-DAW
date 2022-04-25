#pragma once
#include "AppLookAndFeel.h"
#include <juce_gui_extra/juce_gui_extra.h>

class SVGImageComponent : public juce::Component {
  public:
    SVGImageComponent();
    void resized() override;

  private:
    AppLookAndFeel appLookAndFeel;
    std::unique_ptr<juce::Drawable> icon;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SVGImageComponent)
};
