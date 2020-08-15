#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_view_models/app_view_models.h>
#include "TracksView.h"
#include "CurrentTrackView.h"
#include "MidiCommandManager.h"

class EditView : public juce::TabbedComponent,
                 public MidiCommandManager::Listener
{
public:
    EditView(tracktion_engine::Edit& e, MidiCommandManager& mcm, app_view_models::MidiCommandManager& avmmcm, tracktion_engine::SelectionManager& sm);
    ~EditView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void tracksButtonReleased() override;

    void showTrack(tracktion_engine::AudioTrack* t);

private:
    tracktion_engine::Edit& edit;
    MidiCommandManager& midiCommandManager;
    app_view_models::MidiCommandManager& avmMidiCommandManager;
    tracktion_engine::SelectionManager& selectionManager;
    std::unique_ptr<TracksView> tracksView;
    std::unique_ptr<CurrentTrackView> currentTrackView;


    juce::String tracksTabName = "TRACKS";
    juce::String currentTrackTabName = "CURRENT_TRACK";

    void createTracksAndAssignInputs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditView)
};

