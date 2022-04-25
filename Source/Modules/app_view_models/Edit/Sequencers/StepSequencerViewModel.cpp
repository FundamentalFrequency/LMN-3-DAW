namespace app_view_models
{

    StepSequencerViewModel::StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      state(track->state.getOrCreateChildWithName(IDs::STEP_SEQUENCER_STATE, nullptr)),
      stepSequence(state.getOrCreateChildWithName(app_models::IDs::STEP_SEQUENCE, nullptr))
    {

        jassert(state.hasType(IDs::STEP_SEQUENCER_STATE));

        state.addListener(this);

        std::function<int(int)> numberOfNotesConstrainer = [this](int param) {

            // numberOfNotes cannot be less than 1
            // it also cannot be greater than the maximum number of notes allowed
            if (param <= 1)
                return 1;
            else if (param >= app_models::StepChannel::maxNumberOfNotes)
                return app_models::StepChannel::maxNumberOfNotes;
            else
                return param;

        };

        numberOfNotes.setConstrainer(numberOfNotesConstrainer);
        numberOfNotes.referTo(state, IDs::numberOfNotes, nullptr, app_models::StepChannel::maxNumberOfNotes);

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

        notesPerMeasure.referTo(state, IDs::notesPerMeasure, nullptr, 4);


        double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);


        // Midi clip
        midiClipStart = track->edit.getTransport().getCurrentPosition();
        midiClipEnd = midiClipStart + (numberOfNotes.get() * ( 4.0 / double(notesPerMeasure.get())) * secondsPerBeat);
        const tracktion_engine::EditTimeRange midiClipTimeRange(midiClipStart, midiClipEnd);



        midiClip = dynamic_cast<tracktion_engine::MidiClip*>(track->insertNewClip(tracktion_engine::TrackItem::Type::midi, "step", midiClipTimeRange, nullptr));

        generateMidiSequence();

        loopAroundClip(*midiClip);

        track->edit.getTransport().addListener(this);


    }

    StepSequencerViewModel::~StepSequencerViewModel()
    {


        stop();

        generateMidiSequence();

        // if the sequence is empty, delete the clip
        // and disable looping
        if (midiClip->getSequence().isEmpty())
        {

            midiClip->removeFromParentTrack();
            track->edit.getTransport().looping.setValue(false, nullptr);

        }


        state.removeListener(this);
        track->edit.getTransport().removeListener(this);



    }

    int StepSequencerViewModel::getNumChannels()
    {

        return app_models::StepChannel::maxNumberOfChannels;

    }

    int StepSequencerViewModel::getNumNotesPerChannel()
    {

        return app_models::StepChannel::maxNumberOfNotes;

    }

    bool StepSequencerViewModel::hasNoteAt(int channel, int noteIndex)
    {

        return stepSequence.getChannel(channel)->getNote(noteIndex);

    }


    void StepSequencerViewModel::toggleNoteNumberAtSelectedIndex(int noteNumber)
    {

        if (!track->edit.getTransport().isPlaying())
        {

            int channel = noteNumberToChannel(noteNumber);
            stepSequence.getChannel(channel)->setNote(selectedNoteIndex.get(), !stepSequence.getChannel(channel)->getNote(selectedNoteIndex.get()));
            incrementSelectedNoteIndex();

        }

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

        if (!track->edit.getTransport().isPlaying())
            numberOfNotes.setValue(numberOfNotes.get() + 1, nullptr);

    }

    void StepSequencerViewModel::decrementNumberOfNotes()
    {

        if (!track->edit.getTransport().isPlaying())
            numberOfNotes.setValue(numberOfNotes.get() - 1, nullptr);

    }

    int StepSequencerViewModel::getNotesPerMeasure()
    {

        return notesPerMeasure.get();

    }

    void StepSequencerViewModel::incrementNotesPerMeasure()
    {

        if (!track->edit.getTransport().isPlaying())
        {

            int currentIndex = notesPerMeasureOptions.indexOf(notesPerMeasure.get());

            if (currentIndex != -1) {

                int newIndex;
                if (currentIndex == notesPerMeasureOptions.size() - 1)
                    newIndex = 0;
                else
                    newIndex = currentIndex + 1;


                notesPerMeasure.setValue(notesPerMeasureOptions[newIndex], nullptr);

            }
        }

    }

    void StepSequencerViewModel::decrementNotesPerMeasure()
    {

        if (!track->edit.getTransport().isPlaying())
        {

            int currentIndex = notesPerMeasureOptions.indexOf(notesPerMeasure.get());

            if (currentIndex != -1)
            {

                int newIndex;
                if (currentIndex == 0)
                    newIndex = notesPerMeasureOptions.size() - 1;
                else
                    newIndex = currentIndex  - 1;

                notesPerMeasure.setValue(notesPerMeasureOptions[newIndex], nullptr);

            }

        }

    }

    void StepSequencerViewModel::clearNotesAtSelectedIndex()
    {

        if (!track->edit.getTransport().isPlaying())
            for (int i = 0; i < app_models::StepChannel::maxNumberOfChannels; i++)
                stepSequence.getChannel(i)->setNote(selectedNoteIndex, false);

    }

    void StepSequencerViewModel::play()
    {

        if (!track->edit.getTransport().isPlaying())
        {

            generateMidiSequence();
            track->edit.clickTrackEnabled.setValue(false, nullptr);
            track->edit.getTransport().setCurrentPosition(midiClipStart);
            track->setSolo(true);
            track->edit.getTransport().play(false);

        }

    }

    void StepSequencerViewModel::stop()
    {

        if (track->edit.getTransport().isPlaying())
        {

            track->edit.clickTrackEnabled.setValue(true, nullptr);
            track->setSolo(false);
            track->edit.getTransport().stop(false, false);

        }


    }

    void StepSequencerViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdatePattern))
        {

            listeners.call([this](Listener &l) { l.patternChanged(); });
            // generateMidiSequence();

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

        if (compareAndReset(shouldUpdateNotesPerMeasure))
            listeners.call([this](Listener &l) { l.notesPerMeasureChanged(notesPerMeasure.get()); });

    }

    void StepSequencerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged.hasType(app_models::IDs::STEP_CHANNEL))
            if (property == app_models::IDs::stepPattern)
                markAndUpdate(shouldUpdatePattern);


        if (treeWhosePropertyHasChanged == state)
        {

            if (property == IDs::selectedNoteIndex)
                markAndUpdate(shouldUpdateSelectedNoteIndex);

            if (property == IDs::numberOfNotes)
            {


                double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);
                midiClipEnd = midiClipStart + (numberOfNotes.get() * ( 4.0 / double(notesPerMeasure.get())) * secondsPerBeat);
                midiClip->setEnd(midiClipEnd, true);
                loopAroundClip(*midiClip);

                markAndUpdate(shouldUpdateNumberOfNotes);

            }


            if (property == IDs::notesPerMeasure)
            {

                double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);
                midiClipEnd = midiClipStart + (numberOfNotes.get() * ( 4.0 / double(notesPerMeasure.get())) * secondsPerBeat);
                midiClip->setEnd(midiClipEnd, true);
                loopAroundClip(*midiClip);

                markAndUpdate(shouldUpdateNotesPerMeasure);

            }


        }

    }

    void StepSequencerViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->patternChanged();
        l->selectedNoteIndexChanged(selectedNoteIndex.get());
        l->numberOfNotesChanged(numberOfNotes.get());
        l->notesPerMeasureChanged(notesPerMeasure.get());

    }

    void StepSequencerViewModel::removeListener(Listener *l)
    {
        listeners.remove(l);
    }



    void StepSequencerViewModel::generateMidiSequence()
    {

        auto& sequence = midiClip->getSequence();
        sequence.clear(nullptr);

        for (int i = 0; i < getNumChannels(); i++)
            for (int j = 0; j < getNumNotesPerChannel(); j++)
                if (hasNoteAt(i, j))
                    sequence.addNote(i + 53, double(j * 4.0) / double(notesPerMeasure.get()), 4.0 / double(notesPerMeasure.get()), 96, 1, nullptr);


    }

    void StepSequencerViewModel::setVideoPosition(double time, bool forceJump)
    {

        // find beat of current time relative to the start of the midi clip
        // round it down to nearest whole beat
        // then account for the notes per measure
        double beatTime = floorToFraction(track->edit.tempoSequence.timeToBeats(time - midiClipStart), double(notesPerMeasure.get()) / 4.0);
        int note = (beatTime * notesPerMeasure.get()) / 4.0;
        selectedNoteIndex.setValue(note, nullptr);

    }

    double StepSequencerViewModel::floorToFraction(double number, double denominator)
    {

        // https://stackoverflow.com/questions/14903379/rounding-to-nearest-fraction-half-quarter-etc
        double x = number * denominator;
        x = floor(x);
        x = x / denominator;
        return x;

    }

}
