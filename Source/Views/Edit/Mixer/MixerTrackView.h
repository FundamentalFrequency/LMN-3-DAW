#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_view_models/app_view_models.h>
#include "LabeledKnob.h"
#include "SelectionShroud.h"
#include "AppLookAndFeel.h"
class MixerTrackView
        : public juce::Component,
          public app_view_models::MixerTrackViewModel::Listener,
          private juce::Timer
{
public:

    MixerTrackView(tracktion_engine::AudioTrack::Ptr t);
    ~MixerTrackView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelected(bool selected);

    void panChanged(double pan) override;
    void volumeChanged(double volume) override;



private:

    tracktion_engine::AudioTrack::Ptr track;
    app_view_models::MixerTrackViewModel viewModel;
    bool isSelected = false;

    LabeledKnob panKnob;

    juce::Slider volumeSlider;

    juce::Grid grid;

    AppLookAndFeel appLookAndFeel;

    SelectionShroud selectionShroud;

    void timerCallback() override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerTrackView)
};

