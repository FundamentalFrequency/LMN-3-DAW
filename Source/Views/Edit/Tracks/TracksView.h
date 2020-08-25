#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <fontaudio/fontaudio.h>
#include "TracksListBoxModel.h"
#include "BinaryData.h"
#include "PlayheadComponent.h"

class TracksView : public juce::Component,
                   public app_services::MidiCommandManager::Listener,
                   public app_view_models::TracksViewModel::Listener
{
public:
    TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm);
    ~TracksView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void encoder4ButtonReleased() override;

    void recordButtonReleased() override;
    void playButtonReleased() override;
    void stopButtonReleased() override;

    void singleTrackViewButtonReleased() override;
    void tracksButtonReleased() override;

    void selectedTrackIndexChanged(int newIndex) override;
    void isRecordingChanged(bool isRecording);
    void isPlayingChanged(bool isPlaying);
    void tracksChanged() override;
    void tracksViewTypeChanged(app_view_models::TracksViewModel::TracksViewType type) override;

private:

    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    tracktion_engine::SelectionManager& selectionManager;
    app_view_models::TracksViewModel viewModel;
    juce::ListBox singleTrackListBox;
    juce::ListBox multiTrackListBox;
    std::unique_ptr<TracksListBoxModel> listModel;

    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
    juce::Label playingLabel;
    juce::Label recordingLabel;

    PlayheadComponent playheadComponent;

    // Font awesome typeface for play and stop buttons since fontaudio does not have filled icons
    Typeface::Ptr faTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::FontAwesome5FreeSolid900_otf, BinaryData::FontAwesome5FreeSolid900_otfSize);
    juce::Font faFont = juce::Font(faTypeface);

    juce::String playIcon = juce::String::charToString(0xf04b);
    fontaudio::IconName recordIcon = fontaudio::Armrecording;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

