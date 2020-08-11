#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "MidiCommandManager.h"
class PluginView
    : public juce::Component,
      public MidiCommandManager::Listener
{

public:
    explicit PluginView(MidiCommandManager& mcm, Component* plugin);
    ~PluginView() override;
    void paint(juce::Graphics&) override;
    void resized() override;
private:

    MidiCommandManager& midiCommandManager;
    juce::Component::SafePointer<juce::Component> pluginComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);

};


