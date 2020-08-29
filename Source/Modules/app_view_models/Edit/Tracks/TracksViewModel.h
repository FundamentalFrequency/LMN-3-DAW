#pragma once

namespace app_view_models {


        namespace IDs {

            const juce::Identifier TRACKS_VIEW_STATE("TRACKS_VIEW_STATE");
            const juce::Identifier selectedTrackIndex("selectedTrackIndex");
            const juce::Identifier tracksViewType("tracksViewType");

        }

    class TracksViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater,
          private juce::ChangeListener,
          private tracktion_engine::TransportControl::Listener
    {

    public:

        enum class TracksViewType
        {
            MULTI_TRACK,
            SINGLE_TRACK
        };

        TracksViewModel(tracktion_engine::Edit& e, tracktion_engine::SelectionManager& sm, app_services::TimelineCamera& cam);
        ~TracksViewModel();

        void initialiseInputs();
        int getSelectedTrackIndex();
        void setSelectedTrackIndex(int newIndex);

        TracksViewType getTracksViewType();
        void setTracksViewType(TracksViewType type);

        juce::Array<tracktion_engine::AudioTrack*> getTracks();

        tracktion_engine::AudioTrack::Ptr getSelectedTrack();

        void deleteSelectedTrack();
        void addTrack();

        void startRecording();
        void startPlaying();
        void stopRecordingOrPlaying();
        void nudgeTransportForward();
        void nudgeTransportBackward();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedTrackIndexChanged(int newIndex) {};
            virtual void isRecordingChanged(bool isRecording) {};
            virtual void isPlayingChanged(bool isPlaying) {};
            virtual void tracksViewTypeChanged(TracksViewType type) {};
            virtual void tracksChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::Edit& edit;
        // this is the TRACKS_VIEW_STATE value tree that is a child of the edit value tree
        juce::ValueTree state;
        tracktion_engine::SelectionManager& selectionManager;
        app_services::TimelineCamera& camera;
        tracktion_engine::ConstrainedCachedValue<int> selectedTrackIndex;
        juce::CachedValue<int> tracksViewType;
        juce::ListenerList<Listener> listeners;

        // async update markers
        bool shouldUpdateTracks = false;
        bool shouldUpdateSelectedIndex = false;
        bool shouldUpdateTracksViewType = false;

        void handleAsyncUpdate() override;

        // used for transport changes
        void changeListenerCallback(juce::ChangeBroadcaster*) override;
        void playbackContextChanged() override {};
        void autoSaveNow() override {};
        void setAllLevelMetersActive (bool) override {};
        void setVideoPosition (double time, bool forceJump) override;
        void startVideo() override {};
        void stopVideo() override {};

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;


    };

}



