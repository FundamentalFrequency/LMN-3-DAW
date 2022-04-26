#pragma once
#include "AppLookAndFeel.h"
#include <juce_gui_extra/juce_gui_extra.h>
class MessageBox : public juce::Component {
  public:
    MessageBox();
    void paint(juce::Graphics &) override;
    void resized() override;
    juce::String getMessage();
    void setMessage(const juce::String &message);
    juce::Font getFont();

  private:
    AppLookAndFeel appLookAndFeel;
    juce::Label messageLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageBox)
};
