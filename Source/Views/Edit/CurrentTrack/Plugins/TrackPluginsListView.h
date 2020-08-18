#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_services/app_services.h>
#include "TrackPluginsListBoxModel.h"

class TrackPluginsListView
        : public juce::Component,
          public app_services::MidiCommandManager::Listener
{
public:

    enum ColourIds
    {
        leftSelectedBackgroundColourId = 0x1003281,
        rightSelectedBackgroundColourId = 0x1003282
    };

    TrackPluginsListView(tracktion_engine::AudioTrack* t, app_services::MidiCommandManager& mcm);
    ~TrackPluginsListView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void lookAndFeelChanged() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;
    void encoder4ButtonReleased() override;
    void instrumentPluginsButtonReleased() override;
    void effectsPluginsButtonReleased() override;

private:

    tracktion_engine::AudioTrack* track;
    app_services::MidiCommandManager& midiCommandManager;
    juce::ListBox listBox;
    std::unique_ptr<TrackPluginsListBoxModel> listModel;
    juce::Component* editor = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackPluginsListView)
};




