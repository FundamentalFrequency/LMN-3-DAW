#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_services/app_services.h>
#include "LabeledKnob.h"
#include "AppLookAndFeel.h"

class InternalPluginView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener
{

public:

    InternalPluginView(app_services::MidiCommandManager& mcm);
    ~InternalPluginView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void shiftButtonPressed() override;
    void shiftButtonReleased() override;

private:

    app_services::MidiCommandManager& midiCommandManager;
    juce::Label titleLabel;
    juce::OwnedArray<LabeledKnob> knobs;

    AppLookAndFeel appLookAndFeel;

    juce::Grid grid1;
    juce::Grid grid2;
    void gridSetup();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InternalPluginView)

};


