namespace app_models
{

    namespace IDs
    {

        const juce::Identifier STEP_PATTERN("STEP_PATTERN");
        const juce::Identifier CHANNEL("CHANNEL");
        const juce::Identifier channelIndex("channelIndex");
        const juce::Identifier noteSequence("noteSequence");

    }
    class StepPattern
    {

    public:

        StepPattern(juce::ValueTree v);

        juce::BigInteger getNoteSequenceAtChannel(int channelIndex);
        void setNoteSequenceAtChannel(int channelIndex, juce::BigInteger b);

        bool getNote(int channelIndex, int noteIndex);

        void setNote(int channelIndex, int noteIndex, bool value);

        juce::ValueTree state;

        const int numberOfNotes = 16;
        const int numberOfChannels = 24;

    };


}


