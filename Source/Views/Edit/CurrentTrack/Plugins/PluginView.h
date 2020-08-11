#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "MidiCommandManager.h"
class PluginView
    : public juce::Component,
      public MidiCommandManager::Listener
{

public:
    explicit PluginView(MidiCommandManager& mcm);
    ~PluginView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void setViewedComponent(Component* const newComponent);

private:

    MidiCommandManager& midiCommandManager;
    juce::Component* contentComponent = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);

};


