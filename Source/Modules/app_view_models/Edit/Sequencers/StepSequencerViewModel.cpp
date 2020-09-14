#include "StepSequencerViewModel.h"

namespace app_view_models
{

    StepSequencerViewModel::StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      noteIndexMarkerState(track->edit.state.getOrCreateChildWithName(IDs::STEP_SEQUENCER_STATE, nullptr).getOrCreateChildWithName(IDs::noteIndexMarker,
                                                                                                                                   nullptr), 16),
      maxNumberOfNotesState(track->edit.state.getOrCreateChildWithName(IDs::STEP_SEQUENCER_STATE, nullptr).getOrCreateChildWithName(IDs::maxNumberOfNotes,
                                                                                                                                    nullptr), 16)
    {

        // Find length of 4 bars (16 beats)
        double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);
        double startTime = track->edit.getTransport().getCurrentPosition();
        double endTime = startTime + 16 * secondsPerBeat;
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
        stepClip->getPattern(0).setNote(channel, noteIndexMarkerState.getSelectedItemIndex(), !hasNoteAt(channel, noteIndexMarkerState.getSelectedItemIndex()));

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

    void StepSequencerViewModel::incrementSelectedNoteIndex()
    {

        noteIndexMarkerState.setSelectedItemIndex(noteIndexMarkerState.getSelectedItemIndex() + 1);

    }

    void StepSequencerViewModel::decrementSelectedNoteIndex()
    {

        noteIndexMarkerState.setSelectedItemIndex(noteIndexMarkerState.getSelectedItemIndex() - 1);

    }

    void StepSequencerViewModel::incrementMaxNumberOfNotes()
    {

        maxNumberOfNotesState.setSelectedItemIndex(maxNumberOfNotesState.getSelectedItemIndex() + 1);

        noteIndexMarkerState.listSize = maxNumberOfNotesState.getSelectedItemIndex();

    }

    void StepSequencerViewModel::decrementMaxNumberOfNotes()
    {

        maxNumberOfNotesState.setSelectedItemIndex(maxNumberOfNotesState.getSelectedItemIndex() - 1);

        if (noteIndexMarkerState.getSelectedItemIndex() > maxNumberOfNotesState.getSelectedItemIndex())
            noteIndexMarkerState.setSelectedItemIndex(maxNumberOfNotesState.getSelectedItemIndex());

        noteIndexMarkerState.listSize = maxNumberOfNotesState.getSelectedItemIndex();

    }

    void StepSequencerViewModel::handleAsyncUpdate()
    {

        if (shouldUpdatePattern)
            listeners.call([this](Listener &l) { l.patternChanged(); });

    }

    void StepSequencerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

            markAndUpdate(shouldUpdatePattern);

    }

    void StepSequencerViewModel::addListener(Listener *l)
    {
        listeners.add(l);
        l->patternChanged();
    }

    void StepSequencerViewModel::removeListener(Listener *l)
    {
        listeners.remove(l);
    }

}
