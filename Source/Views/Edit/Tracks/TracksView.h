#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TracksListBoxModel.h"
#include "MidiCommandManager.h"
class TracksView : public juce::Component,
                   public MidiCommandManager::Listener
{
public:
    TracksView(juce::Array<tracktion_engine::AudioTrack*> ts, MidiCommandManager& mcm);
    ~TracksView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

private:

    MidiCommandManager& midiCommandManager;
    juce::ListBox listBox;
    std::unique_ptr<TracksListBoxModel> listModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

