#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>
#include "LabeledKnob.h"
#include "AppLookAndFeel.h"
#include "PluginKnobs.h"

// Note this class is very heavy. It should probably be refactored but this generic plugin view
// is really just a holdover until each plugin has its own specialized view so I feel its not worth it at this
// point in time

class InternalPluginView
: public juce::TabbedComponent,
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

    void init();

    ~InternalPluginView() override;

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

    void plusButtonReleased() override;
    void minusButtonReleased() override;

    void parametersChanged() override;
private:
    // This includes the parameters that appear when pressing the ctrl button
    const int PARAMETERS_PER_PAGE = 8;
    std::unique_ptr<app_view_models::InternalPluginViewModel> viewModel;
    app_services::MidiCommandManager& midiCommandManager;
    juce::Label titleLabel;
    juce::Label pageLabel;

    AppLookAndFeel appLookAndFeel;

    int getNumTabs();
    int getNumEnabledParametersForTab(int tabIndex);
    [[nodiscard]] int getParameterIndex(int tabIndex, int knobIndex) const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InternalPluginView)
};


