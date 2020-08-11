#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TracksView.h"
#include "CurrentTrackView.h"
#include "MidiCommandManager.h"

class EditView : public juce::TabbedComponent,
                 public MidiCommandManager::Listener
{
public:
    EditView(tracktion_engine::Edit& e, MidiCommandManager& mcm);
    ~EditView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void tracksButtonReleased() override;

    void showTrack(tracktion_engine::AudioTrack* t);

private:
    tracktion_engine::Edit& edit;
    MidiCommandManager& midiCommandManager;

    std::unique_ptr<TracksView> tracksView;
    std::unique_ptr<CurrentTrackView> currentTrackView;


    juce::String tracksTabName = "TRACKS";
    juce::String currentTrackTabName = "CURRENT_TRACK";

    void createTracksAndAssignInputs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditView)
};

