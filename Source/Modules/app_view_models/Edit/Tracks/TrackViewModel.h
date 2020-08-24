#pragma once

namespace app_view_models {

    namespace IDs {

        const juce::Identifier TRACK_VIEW_STATE("TRACK_VIEW_STATE");

    }

    class TrackViewModel
            : public juce::ValueTree::Listener,
              private juce::ChangeListener,
              public FlaggedAsyncUpdater
    {

    public:
        TrackViewModel(tracktion_engine::AudioTrack& t, tracktion_engine::SelectionManager& sm);
        ~TrackViewModel();

        void deleteClipAtPlayHead();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void clipsChanged(const juce::Array<tracktion_engine::Clip*>& clips) {};
            virtual void clipPositionsChanged(const juce::Array<tracktion_engine::Clip*>& clips) {};
            virtual void recordingStatusChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::AudioTrack& track;
        // this is the TRACK_VIEW_STATE value tree that is a child of the track value tree
        juce::ValueTree state;
        tracktion_engine::SelectionManager& selectionManager;
        juce::ListenerList<Listener> listeners;

        // Async updater flags
        bool shouldUpdateClips = false;
        bool shouldUpdateClipPositions = false;
        bool shouldUpdateRecordingStatus = false;

        void handleAsyncUpdate() override;

        // used for transport changes
        void changeListenerCallback(juce::ChangeBroadcaster*) override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
        void valueTreeChildOrderChanged(juce::ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;

    };

}


