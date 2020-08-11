#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "TrackPluginsListBoxModel.h"
#include "MidiCommandManager.h"

class TrackPluginsListView
        : public juce::Component,
          public MidiCommandManager::Listener
{
public:

    enum ColourIds
    {
        leftSelectedBackgroundColourId = 0x1003281,
        rightSelectedBackgroundColourId = 0x1003282
    };

    TrackPluginsListView(tracktion_engine::AudioTrack* t, MidiCommandManager& mcm);
    ~TrackPluginsListView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void lookAndFeelChanged() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder4ButtonReleased() override;

private:

    tracktion_engine::AudioTrack* track;
    MidiCommandManager& midiCommandManager;
    juce::ListBox listBox;
    std::unique_ptr<TrackPluginsListBoxModel> listModel;
    juce::Component* editor = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackPluginsListView)
};




