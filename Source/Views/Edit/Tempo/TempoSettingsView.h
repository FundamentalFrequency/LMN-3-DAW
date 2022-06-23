#pragma once
#include "AppLookAndFeel.h"
#include "BeatSettingsComponent.h"
#include "FontData.h"
#include "LabelColour1LookAndFeel.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class TempoSettingsView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::TempoSettingsViewModel::Listener {
  public:
    TempoSettingsView(tracktion::Edit &e,
                      app_services::MidiCommandManager &mcm);
    ~TempoSettingsView();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    void encoder4Increased() override;
    void encoder4Decreased() override;

    void tempoSettingsButtonPressed() override;

    void bpmChanged(const double newBpm, const double newBps) override;
    void clickTrackGainChanged(const double newGain) override;
    void tapModeChanged(const bool newTapMode) override;

  private:
    tracktion::Edit &edit;
    app_view_models::TempoSettingsViewModel viewModel;
    app_services::MidiCommandManager &midiCommandManager;

    BeatSettingsComponent beatSettingsComponent;

    juce::Label gainIcon;
    juce::Slider gainSlider;

    juce::Typeface::Ptr fontAwesomeTypeface =
        juce::Typeface::createSystemTypefaceFor(
            FontData::FontAwesome6FreeSolid900_otf,
            FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(fontAwesomeTypeface);
    juce::Label tapIcon;

    LabelColour1LookAndFeel labelColour1LookAndFeel;
    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TempoSettingsView)
};
