#pragma once
#include "AppLookAndFeel.h"
#include "FontData.h"
#include <app_services/app_services.h>
#include <juce_gui_extra/juce_gui_extra.h>

class ControlButtonIndicator
    : public juce::Component,
      public app_services::MidiCommandManager::Listener {
  public:
    explicit ControlButtonIndicator(app_services::MidiCommandManager &mcm);
    ~ControlButtonIndicator() override;
    void controlButtonPressed() override;
    void controlButtonReleased() override;
    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    app_services::MidiCommandManager &midiCommandManager;
    juce::Typeface::Ptr fontAwesomeTypeface =
        juce::Typeface::createSystemTypefaceFor(
            FontData::FontAwesome6FreeSolid900_otf,
            FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(fontAwesomeTypeface);
    AppLookAndFeel appLookAndFeel;
    juce::Label iconLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlButtonIndicator)
};
