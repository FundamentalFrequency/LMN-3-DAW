#pragma once

namespace app_view_models
{

    namespace IDs {

        const juce::Identifier STEP_SEQUENCER_STATE("STEP_SEQUENCER_VIEW_STATE");
        const juce::Identifier selectedNoteIndex("selectedNoteIndex");
        const juce::Identifier numberOfNotes("numberOfNotes");

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

        int getSelectedNoteIndex();
        int getNumberOfNotes();

        void incrementSelectedNoteIndex();
        void decrementSelectedNoteIndex();

        void incrementNumberOfNotes();
        void decrementNumberOfNotes();

        void clearNotesAtSelectedIndex();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void patternChanged() {};
            virtual void selectedNoteIndexChanged(int newIndex) {};
            virtual void numberOfNotesChanged(int newNumberOfNotes) {};


        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

        const int MAXIMUM_NUMBER_OF_NOTES = 16;

    private:
        tracktion_engine::AudioTrack::Ptr track;
        tracktion_engine::StepClip::Ptr stepClip;

        juce::ValueTree state;

        tracktion_engine::ConstrainedCachedValue<int> selectedNoteIndex;
        tracktion_engine::ConstrainedCachedValue<int> numberOfNotes;

        juce::ValueTree patternState;

        juce::ListenerList<Listener> listeners;

        // Async update markers
        bool shouldUpdatePattern = false;
        bool shouldUpdateSelectedNoteIndex = false;
        bool shouldUpdateNumberOfNotes = false;

        void handleAsyncUpdate() override;
        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;


    };

}

