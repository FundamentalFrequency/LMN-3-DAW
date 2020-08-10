#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TracksView.h"
#include "CurrentTrackView.h"
#include "MidiCommandManager.h"

class EditView : public juce::TabbedComponent,
                 public juce::ApplicationCommandTarget
{
public:
    EditView(tracktion_engine::Edit& e, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:
    tracktion_engine::Edit& edit;
    juce::ApplicationCommandManager& commandManager;
    MidiCommandManager midiCommandManager;

    std::unique_ptr<TracksView> tracksView;
    std::unique_ptr<CurrentTrackView> currentTrackView;


    juce::String tracksTabName = "TRACKS";
    juce::String currentTrackTabName = "CURRENT_TRACK";

    void createTracksAndAssignInputs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditView)
};

