#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "TracksListBoxModel.h"
#include "PlayheadComponent.h"
#include "BeatMarkerComponent.h"
#include "InformationPanelComponent.h"
#include "TrackView.h"

class TracksView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::TracksViewModel::Listener,
      private juce::Timer
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

    void plusButtonReleased() override;
    void minusButtonReleased() override;

    void pluginsButtonReleased() override;

    void recordButtonReleased() override;
    void playButtonReleased() override;
    void stopButtonReleased() override;

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
    app_services::TimelineCamera camera;
    app_view_models::TracksViewModel viewModel;

    InformationPanelComponent informationPanel;
    juce::ListBox singleTrackListBox;
    juce::ListBox multiTrackListBox;
    std::unique_ptr<TracksListBoxModel> listModel;

    std::unique_ptr<TrackView> singleTrackView;

    PlayheadComponent playheadComponent;

    juce::OwnedArray<BeatMarkerComponent> beats;
    void buildBeats();

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

