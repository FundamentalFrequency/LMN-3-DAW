#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <app_navigation/app_navigation.h>
#include "TracksView.h"
#include "TempoSettingsView.h"

class EditView : public juce::TabbedComponent,
                 public app_services::MidiCommandManager::Listener
{
public:
    EditView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm);
    ~EditView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void tracksButtonReleased() override;

    void tempoSettingsButtonReleased() override;
    void showTrack(tracktion_engine::AudioTrack* t);

private:
    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    std::unique_ptr<app_navigation::StackNavigationController> stackNavigationController;
    std::unique_ptr<TempoSettingsView> tempoSettingsView;
    juce::String tracksTabName = "TRACKS";
    juce::String tempoSettingsTabName = "TEMPO_SETTINGS";


    void createTracksAndAssignInputs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditView)
};

