#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_services/app_services.h>
class InternalPluginView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener
{

public:

    InternalPluginView(app_services::MidiCommandManager& mcm);
    ~InternalPluginView();

private:

    app_services::MidiCommandManager& midiCommandManager;

};


