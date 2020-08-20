#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "TracksListBoxModel.h"

class TracksView : public juce::Component,
                   public app_services::MidiCommandManager::Listener,
                   public app_view_models::TracksViewModel::Listener
{
public:
    TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm);
    ~TracksView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;
    void encoder4ButtonReleased() override;

    void selectedTrackIndexChanged(int newIndex) override;
    void tracksChanged() override;

private:

    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    tracktion_engine::SelectionManager& selectionManager;
    app_view_models::TracksViewModel viewModel;
    juce::ListBox listBox;
    std::unique_ptr<TracksListBoxModel> listModel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

