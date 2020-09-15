#include "StepSequencerViewModel.h"

namespace app_view_models
{

    StepSequencerViewModel::StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      state(track->edit.state.getOrCreateChildWithName(IDs::STEP_SEQUENCER_STATE, nullptr))
    {


        jassert(state.hasType(IDs::STEP_SEQUENCER_STATE));
        state.addListener(this);

        std::function<int(int)> numberOfNotesConstrainer = [this](int param) {

            // numberOfNotes cannot be less than 1
            // it also cannot be greater than the maximum number of notes allowed
            if (param <= 1)
                return 1;
            else if (param >= MAXIMUM_NUMBER_OF_NOTES)
                return MAXIMUM_NUMBER_OF_NOTES;
            else
                return param;

        };

        numberOfNotes.setConstrainer(numberOfNotesConstrainer);
        numberOfNotes.referTo(state, IDs::numberOfNotes, nullptr, MAXIMUM_NUMBER_OF_NOTES);

        std::function<int(int)> selectedNoteIndexConstrainer = [this](int param) {

            // selected index cannot be less than 0
            // it also cannot be greater than or equal to the number of notes
            if (param <= 0)
                return 0;
            else if (param >= numberOfNotes.get())
                return numberOfNotes.get() - 1;
            else
                return param;

        };

        selectedNoteIndex.setConstrainer(selectedNoteIndexConstrainer);
        selectedNoteIndex.referTo(state, IDs::selectedNoteIndex, nullptr, 0);

        // Find length of 4 bars (16 beats)
        double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);
        double startTime = track->edit.getTransport().getCurrentPosition();
        double endTime = startTime + (numberOfNotes.get() * secondsPerBeat);
        const tracktion_engine::EditTimeRange editTimeRange(startTime, endTime);
        stepClip = dynamic_cast<tracktion_engine::StepClip*>(track->insertNewClip(tracktion_engine::TrackItem::Type::step,
                                                                                     "Step Clip",
                                                                                     editTimeRange,
                                                                                     nullptr));

        // Default number of channels is 8, we need to have 24
        while (stepClip->getChannels().size() < 24)
        {
            stepClip->insertNewChannel(stepClip->getChannels().size());
        }

        for (auto channel : stepClip->getChannels())
        {

            for (auto& pattern : stepClip->getPatterns())
                pattern.setNumNotes(16);

        }

        loopAroundClip(*stepClip);



        patternState = stepClip->getPattern(0).state;
        patternState.addListener(this);

    }

    StepSequencerViewModel::~StepSequencerViewModel()
    {

        state.removeListener(this);
        patternState.removeListener(this);

    }

    int StepSequencerViewModel::getNumChannels()
    {

        return stepClip->getChannels().size();

    }

    int StepSequencerViewModel::getNumNotesPerChannel()
    {

        return stepClip->getPattern(0).getNumNotes();

    }

    bool StepSequencerViewModel::hasNoteAt(int channel, int noteIndex)
    {

        return stepClip->getPattern(0).getNote(channel, noteIndex);

    }

    void StepSequencerViewModel::toggleNoteNumberAtSelectedIndex(int noteNumber)
    {

        int channel = noteNumberToChannel(noteNumber);
        stepClip->getPattern(0).setNote(channel, selectedNoteIndex.get(), !hasNoteAt(channel, selectedNoteIndex.get()));

    }

    int StepSequencerViewModel::noteNumberToChannel(int noteNumber)
    {

        juce::String noteName = juce::MidiMessage::getMidiNoteName(noteNumber, true, true, 3);

        // channel 0 corresponds to F
        if (noteName == juce::String("F2"))
            return 0;

        if (noteName == juce::String("F#2"))
            return 1;

        if (noteName == juce::String("G2"))
            return 2;

        if (noteName == juce::String("G#2"))
            return 3;

        if (noteName == juce::String("A2"))
            return 4;

        if (noteName == juce::String("A#2"))
            return 5;

        if (noteName == juce::String("B2"))
            return 6;

        if (noteName == juce::String("C3"))
            return 7;

        if (noteName == juce::String("C#3"))
            return 8;

        if (noteName == juce::String("D3"))
            return 9;

        if (noteName == juce::String("D#3"))
            return 10;

        if (noteName == juce::String("E3"))
            return 11;

        if (noteName == juce::String("F3"))
            return 12;

        if (noteName == juce::String("F#3"))
            return 13;

        if (noteName == juce::String("G3"))
            return 14;

        if (noteName == juce::String("G#3"))
            return 15;

        if (noteName == juce::String("A3"))
            return 16;

        if (noteName == juce::String("A#3"))
            return 17;

        if (noteName == juce::String("B3"))
            return 18;

        if (noteName == juce::String("C4"))
            return 19;

        if (noteName == juce::String("C#4"))
            return 20;

        if (noteName == juce::String("D4"))
            return 21;

        if (noteName == juce::String("D#4"))
            return 22;

        if (noteName == juce::String("E4"))
            return 23;

        return 0;

    }

    int StepSequencerViewModel::getSelectedNoteIndex()
    {

        return selectedNoteIndex.get();

    }

    int StepSequencerViewModel::getNumberOfNotes()
    {

        return numberOfNotes.get();

    }

    void StepSequencerViewModel::incrementSelectedNoteIndex()
    {

        selectedNoteIndex.setValue(selectedNoteIndex.get() + 1, nullptr);

    }

    void StepSequencerViewModel::decrementSelectedNoteIndex()
    {

        selectedNoteIndex.setValue(selectedNoteIndex.get() - 1, nullptr);

    }

    void StepSequencerViewModel::incrementNumberOfNotes()
    {

        numberOfNotes.setValue(numberOfNotes.get() + 1, nullptr);

    }

    void StepSequencerViewModel::decrementNumberOfNotes()
    {

        numberOfNotes.setValue(numberOfNotes.get() - 1, nullptr);


    }

    void StepSequencerViewModel::clearNotesAtSelectedIndex()
    {

        for (int i = 0; i < stepClip->getChannels().size(); i++)
            stepClip->getPattern(0).setNote(i, selectedNoteIndex, false);

    }

    void StepSequencerViewModel::handleAsyncUpdate()
    {

        if (shouldUpdatePattern)
            listeners.call([this](Listener &l) { l.patternChanged(); });

        if (shouldUpdateSelectedNoteIndex)
            listeners.call([this](Listener &l) { l.selectedNoteIndexChanged(selectedNoteIndex.get()); });

        if (shouldUpdateNumberOfNotes)
        {

            listeners.call([this](Listener &l) { l.numberOfNotesChanged(numberOfNotes.get()); });

            if (selectedNoteIndex.get() >= numberOfNotes)
            {

                selectedNoteIndex.setValue(numberOfNotes.get() - 1, nullptr);

            }



        }


    }

    void StepSequencerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

            markAndUpdate(shouldUpdatePattern);

            if (treeWhosePropertyHasChanged == state)
            {

                if (property == IDs::selectedNoteIndex)
                    markAndUpdate(shouldUpdateSelectedNoteIndex);

                if (property == IDs::numberOfNotes)
                    markAndUpdate(shouldUpdateNumberOfNotes);

            }

    }

    void StepSequencerViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->patternChanged();
        l->selectedNoteIndexChanged(selectedNoteIndex.get());
        l->numberOfNotesChanged(numberOfNotes.get());

    }

    void StepSequencerViewModel::removeListener(Listener *l)
    {
        listeners.remove(l);
    }

}
