#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>
#include "LabeledKnob.h"
#include "AppLookAndFeel.h"

class FourOscView
        : public juce::TabbedComponent,
          public app_services::MidiCommandManager::Listener
{

public:

    FourOscView(tracktion_engine::FourOscPlugin* p, app_services::MidiCommandManager& mcm);

    ~FourOscView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void plusButtonReleased() override;
    void minusButtonReleased() override;

private:

    tracktion_engine::FourOscPlugin* plugin;
    app_services::MidiCommandManager& midiCommandManager;

    juce::String osc1TabName = "OSC1";
    juce::String osc2TabName = "OSC2";
    juce::String osc3TabName = "OSC3";
    juce::String osc4TabName = "OSC4";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FourOscView)


};



