#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_view_models/app_view_models.h>
#include <fontaudio/fontaudio.h>
#include "LabeledKnob.h"
#include "SelectionShroud.h"
#include "AppLookAndFeel.h"
#include "LevelMeterComponent.h"

class MixerTrackView
        : public juce::Component,
          public app_view_models::MixerTrackViewModel::Listener
{
public:

    MixerTrackView(tracktion_engine::AudioTrack::Ptr t);
    ~MixerTrackView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelected(bool selected);

    void panChanged(double pan) override;
    void volumeChanged(double volume) override;
    void soloStateChanged(bool solo) override;
    void muteStateChanged(bool mute) override;



private:

    tracktion_engine::AudioTrack::Ptr track;
    app_view_models::MixerTrackViewModel viewModel;
    bool isSelected = false;
    LabeledKnob panKnob;
    juce::Slider volumeSlider;
    juce::Grid grid;
    std::unique_ptr<LevelMeterComponent> levelMeter;

    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
    fontaudio::IconName soloIcon = fontaudio::Solo;
    fontaudio::IconName muteIcon = fontaudio::Mute;
    juce::Label soloLabel;
    juce::Label muteLabel;

    AppLookAndFeel appLookAndFeel;

    SelectionShroud selectionShroud;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerTrackView)
};

