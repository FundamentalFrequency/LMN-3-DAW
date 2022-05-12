#pragma once
#include "AppLookAndFeel.h"
#include "FilterADSRView.h"
#include "LabeledKnob.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_basics/juce_gui_basics.h>
class FilterView : public juce::Component,
                   public app_services::MidiCommandManager::Listener,
                   public app_view_models::FilterViewModel::Listener {
  public:
    FilterView(tracktion_engine::FourOscPlugin *p,
               app_services::MidiCommandManager &mcm);

    ~FilterView();

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
    app_view_models::FilterViewModel viewModel;
    app_services::MidiCommandManager &midiCommandManager;
    juce::Label titleLabel;
    juce::OwnedArray<LabeledKnob> knobs;
    FilterADSRView filterAdsrView;
    AppLookAndFeel appLookAndFeel;

    juce::Grid grid;
    void gridSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterView)
};
