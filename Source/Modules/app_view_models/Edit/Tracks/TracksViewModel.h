#pragma once

namespace app_view_models {


        namespace IDs {

            const juce::Identifier TRACKS_VIEW_STATE("TRACKS_VIEW_STATE");
            const juce::Identifier selectedTrackIndex("selectedTrackIndex");

        }

    class TracksViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater,
          public MidiCommandManager::Listener
    {

    public:

        TracksViewModel(tracktion_engine::Edit& e, MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm);
        ~TracksViewModel();

        juce::Array<juce::String> getTrackNames();

        int getSelectedTrackIndex();
        void setSelectedTrackIndex(int newIndex);


        tracktion_engine::Track* getSelectedTrack();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedTrackIndexChanged(int newIndex) {};
            virtual void tracksChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

        // Midi Command Manager
        void encoder1Increased() override;
        void encoder1Decreased() override;
        void encoder1ButtonReleased() override;

    private:

        tracktion_engine::Edit& edit;
        // this is the TRACKS_VIEW_STATE value tree that is a child of the edit value tree
        juce::ValueTree state;
        MidiCommandManager& midiCommandManager;
        tracktion_engine::SelectionManager& selectionManager;
        tracktion_engine::ConstrainedCachedValue<int> selectedTrackIndex;
        juce::Array<juce::String> trackNames;
        juce::ListenerList<Listener> listeners;

        // async update markers
        bool shouldUpdateTracks = false;
        bool shouldUpdateSelectedIndex = false;

        void updateTrackNames();

        void handleAsyncUpdate() override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;



    };

}



