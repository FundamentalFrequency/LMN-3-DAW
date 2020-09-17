#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "AppLookAndFeel.h"
#include "StepSequencerGridComponent.h"

class StepSequencerView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener
{

public:

    StepSequencerView(tracktion_engine::AudioTrack::Ptr p, app_services::MidiCommandManager& mcm);
    ~StepSequencerView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void noteOnPressed(int noteNumber) override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void playButtonReleased() override;
    void stopButtonReleased() override;


private:

    app_view_models::StepSequencerViewModel viewModel;
    app_services::MidiCommandManager& midiCommandManager;
    AppLookAndFeel appLookAndFeel;
    StepSequencerGridComponent grid;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepSequencerView)

};


