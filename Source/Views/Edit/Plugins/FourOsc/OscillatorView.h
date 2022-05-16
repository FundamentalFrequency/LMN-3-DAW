#pragma once
#include "AppLookAndFeel.h"
#include "Knobs.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_basics/juce_gui_basics.h>

class OscillatorView : public juce::Component,
                       public app_services::MidiCommandManager::Listener,
                       public app_view_models::OscillatorViewModel::Listener {
  public:
    OscillatorView(tracktion_engine::FourOscPlugin *p, int oscIndex,
                   app_services::MidiCommandManager &mcm);

    ~OscillatorView() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    void encoder2Increased() override;
    void encoder2Decreased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void encoder4Increased() override;
    void encoder4Decreased() override;

    void controlButtonPressed() override;
    void controlButtonReleased() override;

    void parametersChanged() override;

  private:
    app_view_models::OscillatorViewModel viewModel;
    app_services::MidiCommandManager &midiCommandManager;
    juce::Label titleLabel;
    Knobs pluginKnobs;
    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorView)
};
