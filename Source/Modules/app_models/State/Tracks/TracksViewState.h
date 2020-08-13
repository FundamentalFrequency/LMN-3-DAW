#pragma once

namespace app_models {

    class TracksViewState
        : private juce::ValueTree::Listener
    {

    public:
        explicit TracksViewState(tracktion_engine::Edit& e);
        ~TracksViewState();

        int getSelectedTrackIndex();
        void setSelectedTrackIndex(int newIndex);
        tracktion_engine::AudioTrack* getSelectedTrack();
        juce::Array<tracktion_engine::AudioTrack*> getAudioTracks();


        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedTrackIndexChanged(int newIndex) {};
            virtual void trackDeleted() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::Edit& edit;

        // this is the EDIT_VIEW_STATE value tree that is a child of the edit value tree
        juce::ValueTree state;
        tracktion_engine::ConstrainedCachedValue<int> selectedTrackIndex;
        juce::ListenerList<Listener> listeners;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
        void valueTreeChildOrderChanged(juce::ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;


    };

}



