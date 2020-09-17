#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include "TracksListBoxModel.h"
#include "PlayheadComponent.h"
#include "LoopMarkerComponent.h"
#include "InformationPanelComponent.h"
#include "TrackView.h"
#include "AppLookAndFeel.h"

class TracksView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::TracksListViewModel::Listener,
      public app_view_models::EditItemListViewModel::Listener,
      public app_view_models::ItemListState::Listener,
      private juce::Timer
{
public:

    TracksView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm);
    ~TracksView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder2Increased() override;
    void encoder2Decreased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void cutButtonReleased() override;
    void pasteButtonReleased() override;

    void splitButtonReleased() override;

    void plusButtonReleased() override;
    void minusButtonReleased() override;

    void sequencersButtonReleased() override;

    void pluginsButtonReleased() override;
    void modifiersButtonReleased() override;

    void loopInButtonReleased() override;
    void loopOutButtonReleased() override;
    void loopButtonReleased() override;

    void recordButtonReleased() override;
    void playButtonReleased() override;
    void stopButtonReleased() override;

    void tracksButtonReleased() override;


    // ItemListState listener methods
    void selectedIndexChanged(int newIndex) override;

    // EditItemListViewModel listener methods
    void itemsChanged() override;

    // TracksListViewModel listener methods
    void isRecordingChanged(bool isRecording) override;
    void isPlayingChanged(bool isPlaying) override;
    void tracksViewTypeChanged(app_view_models::TracksListViewModel::TracksViewType type) override;
    void loopingChanged(bool looping) override;


private:

    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    app_services::TimelineCamera camera;
    app_view_models::TracksListViewModel viewModel;

    InformationPanelComponent informationPanel;
    juce::ListBox singleTrackListBox;
    juce::ListBox multiTrackListBox;
    std::unique_ptr<TracksListBoxModel> listModel;

    std::unique_ptr<TrackView> singleTrackView;

    PlayheadComponent playheadComponent;

    LoopMarkerComponent loopMarkerComponent;

    juce::OwnedArray<juce::DrawableRectangle> beats;
    AppLookAndFeel appLookAndFeel;
    void buildBeats();

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TracksView)
};

