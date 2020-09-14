#pragma once

namespace app_view_models
{

    namespace IDs {

        const juce::Identifier STEP_SEQUENCER_STATE("STEP_SEQUENCER_STATE");
        const juce::Identifier noteIndexMarker("noteIndexMarker");
        const juce::Identifier maxNumberOfNotes("maxNumberOfNotes");

    }

    class StepSequencerViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {
    public:

        StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t);
        ~StepSequencerViewModel();

        int getNumChannels();
        int getNumNotesPerChannel();

        bool hasNoteAt(int channel, int noteIndex);

        void toggleNoteNumberAtSelectedIndex(int noteNumber);

        int noteNumberToChannel(int noteNumber);

        void incrementSelectedNoteIndex();
        void decrementSelectedNoteIndex();

        void incrementMaxNumberOfNotes();
        void decrementMaxNumberOfNotes();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void patternChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);


    private:
        tracktion_engine::AudioTrack::Ptr track;
        tracktion_engine::StepClip::Ptr stepClip;

        juce::ValueTree patternState;

        juce::ListenerList<Listener> listeners;

        // Async update markers
        bool shouldUpdatePattern = false;



        void handleAsyncUpdate() override;
        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

    public:
        ItemListState noteIndexMarkerState;
        ItemListState maxNumberOfNotesState;
    };

}

