namespace app_view_models
{

    StepSequencerViewModel::StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      state(track->state.getOrCreateChildWithName(IDs::STEP_SEQUENCER_STATE, nullptr)),
      stepPattern(initialiseStepPattern(state))
    {


        jassert(state.hasType(IDs::STEP_SEQUENCER_STATE));
        state.addListener(this);

        std::function<int(int)> numberOfNotesConstrainer = [this](int param) {

            // numberOfNotes cannot be less than 1
            // it also cannot be greater than the maximum number of notes allowed
            if (param <= 1)
                return 1;
            else if (param >= stepPattern.numberOfNotes)
                return stepPattern.numberOfNotes;
            else
                return param;

        };

        numberOfNotes.setConstrainer(numberOfNotesConstrainer);
        numberOfNotes.referTo(state, IDs::numberOfNotes, nullptr, stepPattern.numberOfNotes);

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


        double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);


        // Insert midi clip
        midiClipStart = track->edit.getTransport().getCurrentPosition();
        midiClipEnd = midiClipStart + (numberOfNotes.get() * secondsPerBeat);
        const tracktion_engine::EditTimeRange midiClipTimeRange(midiClipStart, midiClipEnd);
        midiClip = dynamic_cast<tracktion_engine::MidiClip*>(track->insertNewClip(tracktion_engine::TrackItem::Type::midi, "clip", midiClipTimeRange, nullptr));
        generateMidiSequence();

        loopAroundClip(*midiClip);


    }

    StepSequencerViewModel::~StepSequencerViewModel()
    {

        state.removeListener(this);

    }

    int StepSequencerViewModel::getNumChannels()
    {

        return stepPattern.numberOfChannels;

    }

    int StepSequencerViewModel::getNumNotesPerChannel()
    {

        return stepPattern.numberOfNotes;

    }

    bool StepSequencerViewModel::hasNoteAt(int channel, int noteIndex)
    {

        return stepPattern.getNote(channel, noteIndex);

    }


    void StepSequencerViewModel::toggleNoteNumberAtSelectedIndex(int noteNumber)
    {

        int channel = noteNumberToChannel(noteNumber);
        stepPattern.setNote(channel, selectedNoteIndex.get(), !stepPattern.getNote(channel, selectedNoteIndex.get()));
        incrementSelectedNoteIndex();

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

        for (int i = 0; i < stepPattern.numberOfChannels; i++)
            stepPattern.setNote(i, selectedNoteIndex, false);

    }

    void StepSequencerViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdatePattern))
        {

            listeners.call([this](Listener &l) { l.patternChanged(); });
            generateMidiSequence();

        }


        if (compareAndReset(shouldUpdateSelectedNoteIndex))
            listeners.call([this](Listener &l) { l.selectedNoteIndexChanged(selectedNoteIndex.get()); });

        if (compareAndReset(shouldUpdateNumberOfNotes))
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

        if (treeWhosePropertyHasChanged.hasType(app_models::IDs::CHANNEL))
            if (property == app_models::IDs::noteSequence)
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

    app_models::StepPattern StepSequencerViewModel::initialiseStepPattern(juce::ValueTree stepSequencerState)
    {

        if (stepSequencerState.getChildWithName(app_models::IDs::STEP_PATTERN).isValid())
        {
            return app_models::StepPattern(stepSequencerState.getChildWithName(app_models::IDs::STEP_PATTERN));
        }
        else
        {

            juce::ValueTree stepPatternTree(app_models::IDs::STEP_PATTERN);
            for (int i = 0; i < 24; i++)
            {

                juce::ValueTree channelTree(app_models::IDs::CHANNEL);
                channelTree.setProperty(app_models::IDs::channelIndex, i, nullptr);

                juce::BigInteger b;
                for (int noteBit = 0; noteBit < 16; noteBit++)
                {
                    b.setBit(noteBit, false);

                }

                channelTree.setProperty(app_models::IDs::noteSequence, b.toString(2), nullptr);
                stepPatternTree.addChild(channelTree, -1, nullptr);
                stepSequencerState.addChild(stepPatternTree, -1, nullptr);

            }

            return app_models::StepPattern(stepPatternTree);

        }

    }

    void StepSequencerViewModel::generateMidiSequence()
    {

        auto& sequence = midiClip->getSequence();
        sequence.clear(nullptr);

        for (int i = 0; i < getNumChannels(); i++)
            for (int j = 0; j < getNumNotesPerChannel(); j++)
                if (hasNoteAt(i, j))
                    sequence.addNote(i + 53, j, 1, 96, 1, nullptr);


    }

}
