namespace app_models
{

    StepPattern::StepPattern(juce::ValueTree v)
        : state(v)
    {



    }

    bool StepPattern::getNote(int channelIndex, int noteIndex)
    {

        return getNoteSequenceAtChannel(channelIndex)[noteIndex];

    }

    void StepPattern::setNote(int channelIndex, int noteIndex, bool value)
    {

        if (getNote(channelIndex, noteIndex) != value
            && juce::isPositiveAndBelow(noteIndex, numberOfNotes)
            && juce::isPositiveAndBelow(channelIndex, numberOfChannels))
        {

            juce::BigInteger b(getNoteSequenceAtChannel(channelIndex));
            b.setBit(noteIndex, value);
            setNoteSequenceAtChannel(channelIndex, b);

        }
    }


    juce::BigInteger StepPattern::getNoteSequenceAtChannel(int channelIndex)
    {

        if (state.getChildWithProperty(IDs::channelIndex, channelIndex).isValid())
        {
            juce::BigInteger b;
            b.parseString(state.getChildWithProperty(IDs::channelIndex, channelIndex).getProperty(IDs::noteSequence).toString(), 2);
            return b;

        }

        return juce::BigInteger();

    }

    void StepPattern::setNoteSequenceAtChannel(int channelIndex, juce::BigInteger b)
    {

        if (state.getChildWithProperty(IDs::channelIndex, channelIndex).isValid())
            state.getChildWithProperty(IDs::channelIndex, channelIndex).setProperty(IDs::noteSequence, b.toString(2),
                                                                                nullptr);

    }

}