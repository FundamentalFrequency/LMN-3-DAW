#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>
#include "LabeledKnob.h"
#include "AppLookAndFeel.h"

class InternalPluginView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::InternalPluginViewModel::Listener
{

public:

    InternalPluginView(tracktion_engine::Plugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::ReverbPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::DelayPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::PhaserPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::ChorusPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::EqualiserPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::CompressorPlugin* p, app_services::MidiCommandManager& mcm);
    InternalPluginView(tracktion_engine::FourOscPlugin* p, app_services::MidiCommandManager& mcm);

    void init();

    ~InternalPluginView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    void encoder2Increased() override;
    void encoder2Decreased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void encoder4Increased() override;
    void encoder4Decreased() override;

    void encoder5Increased() override;
    void encoder5Decreased() override;

    void encoder6Increased() override;
    void encoder6Decreased() override;

    void encoder7Increased() override;
    void encoder7Decreased() override;

    void encoder8Increased() override;
    void encoder8Decreased() override;

    void shiftButtonPressed() override;
    void shiftButtonReleased() override;

    void parametersChanged() override;

private:

    std::unique_ptr<app_view_models::InternalPluginViewModel> viewModel;
    app_services::MidiCommandManager& midiCommandManager;
    juce::Label titleLabel;
    juce::OwnedArray<LabeledKnob> knobs;

    AppLookAndFeel appLookAndFeel;

    juce::Grid grid1;
    juce::Grid grid2;
    void gridSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InternalPluginView)

};


