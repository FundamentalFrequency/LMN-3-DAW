#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_view_models/app_view_models.h>
#include "TracksListBoxModel.h"
#include "MidiCommandManager.h"
class TracksView : public juce::Component,
                   public app_view_models::MidiCommandManager::Listener,
                   public app_view_models::TracksViewModel::Listener
{
public:
    TracksView(tracktion_engine::Edit& e, app_view_models::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm);
    ~TracksView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void selectedTrackIndexChanged(int newIndex) override;

private:

    tracktion_engine::Edit& edit;
    app_view_models::MidiCommandManager& midiCommandManager;
    tracktion_engine::SelectionManager& selectionManager;
    juce::ListBox listBox;
    std::unique_ptr<TracksListBoxModel> listModel;
    app_view_models::TracksViewModel tracksViewModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

