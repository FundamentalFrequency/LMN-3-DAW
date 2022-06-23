#pragma once

namespace app_view_models {

namespace IDs {

const juce::Identifier TRACKS_LIST_VIEW_STATE("TRACKS_LIST_VIEW_STATE");
const juce::Identifier tracksListViewType("tracksListViewType");

} // namespace IDs

class TracksListViewModel : public juce::ValueTree::Listener,
                            public FlaggedAsyncUpdater,
                            private juce::ChangeListener,
                            private tracktion::TransportControl::Listener,
                            private EditItemListViewModel::Listener,
                            private ItemListState::Listener {
  public:
    enum class TracksViewType { MULTI_TRACK, SINGLE_TRACK };

    TracksListViewModel(tracktion::Edit &e, app_services::TimelineCamera &cam);
    ~TracksListViewModel() override;

    void addTrack();
    void deleteSelectedTrack();
    void cutSelectedTracksClipAtPlayHead();
    void pasteClipboardContentToTrackAtPlayhead();
    void splitSelectedTracksClipAtPlayHead();
    void mergeSelectedTracksClipsAtPlayhead();

    TracksViewType getTracksViewType();
    void setTracksViewType(TracksViewType type);

    void startRecording();
    void startPlaying();
    void stopRecordingOrPlaying();
    void nudgeTransportForward();
    void nudgeTransportBackward();
    void nudgeTransportForwardToNearestBeat();
    void nudgeTransportBackwardToNearestBeat();

    void setLoopIn();
    void setLoopOut();
    void toggleLooping();
    void nudgeLoopInForward();
    void nudgeLoopInBackward();
    void nudgeLoopOutForward();
    void nudgeLoopOutBackward();
    void nudgeLoopInForwardToNearestBeat();
    void nudgeLoopInBackwardToNearestBeat();
    void nudgeLoopOutForwardToNearestBeat();
    void nudgeLoopOutBackwardToNearestBeat();

    bool getSelectedTrackSoloState();
    bool getSelectedTrackMuteState();
    void toggleSolo();
    void toggleMute();

    void setSelectedTrackColour(juce::Colour colour);
    juce::Colour getSelectedTrackColour();

    void undo();

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void isRecordingChanged(bool isRecording) {}
        virtual void isPlayingChanged(bool isPlaying) {}
        virtual void tracksViewTypeChanged(TracksViewType type) {}
        virtual void loopingChanged(bool isLooping) {}
        virtual void soloStateChanged(bool solo) {}
        virtual void muteStateChanged(bool mute) {}
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

  private:
    tracktion::Edit &edit;
    app_services::TimelineCamera &camera;
    std::unique_ptr<TracksListAdapter> adapter;
    juce::ValueTree state;

    juce::CachedValue<int> tracksViewType;
    juce::ListenerList<Listener> listeners;

    // async update markers
    bool shouldUpdateTracksViewType = false;
    bool shouldUpdateLooping = false;
    bool shouldUpdateSolo = false;
    bool shouldUpdateMute = false;

    void initialiseInputs();

    void handleAsyncUpdate() override;

    // used to arm newly selected track
    void selectedIndexChanged(int newIndex) override;

    // used for transport changes
    void changeListenerCallback(juce::ChangeBroadcaster *) override;
    void playbackContextChanged() override {}
    void autoSaveNow() override {}
    void setAllLevelMetersActive(bool) override {}
    void setVideoPosition(tracktion::TimePosition timePosition,
                          bool forceJump) override;
    void startVideo() override {}
    void stopVideo() override {}

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

  public:
    // Must appear below the other variables since it needs to be initialized
    // last
    EditItemListViewModel listViewModel;
};

} // namespace app_view_models
