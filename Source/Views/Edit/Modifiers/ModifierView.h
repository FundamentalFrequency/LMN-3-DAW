#pragma once
#include "AppLookAndFeel.h"
#include "LabeledKnob.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_basics/juce_gui_basics.h>

class ModifierView : public juce::Component,
                     public app_services::MidiCommandManager::Listener,
                     public app_view_models::ModifierViewModel::Listener {
  public:
    ModifierView(tracktion_engine::Modifier *mod,
                 app_services::MidiCommandManager &mcm);
    ModifierView(tracktion_engine::LFOModifier *mod,
                 app_services::MidiCommandManager &mcm);

    void init();

    ~ModifierView();

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

    void shiftButtonPressed() override;
    void shiftButtonReleased() override;

    void parametersChanged() override;

  private:
    std::unique_ptr<app_view_models::ModifierViewModel> viewModel;
    app_services::MidiCommandManager &midiCommandManager;
    juce::Label titleLabel;
    juce::OwnedArray<LabeledKnob> knobs;

    AppLookAndFeel appLookAndFeel;

    juce::Grid grid1;
    juce::Grid grid2;
    void gridSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModifierView)
};
