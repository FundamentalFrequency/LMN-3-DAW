#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_view_models/app_view_models.h>
#include "AppLookAndFeel.h"

class StepSequencerGridComponent
        : public juce::Component,
          app_view_models::StepSequencerViewModel::Listener,
          public app_view_models::ItemListState::Listener
{

public:

    StepSequencerGridComponent(app_view_models::StepSequencerViewModel& vm);
    ~StepSequencerGridComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void patternChanged() override;
    void selectedIndexChanged(int newIndex) override;

private:

    app_view_models::StepSequencerViewModel& viewModel;
    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepSequencerGridComponent)

};

