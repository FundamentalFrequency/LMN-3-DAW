namespace app_models {

namespace IDs {

const juce::Identifier STEP_CHANNEL("STEP_CHANNEL");
const juce::Identifier stepChannelIndex("channelIndex");
const juce::Identifier stepPattern("stepPattern");

} // namespace IDs
class StepChannel {
  public:
    StepChannel(juce::ValueTree v);

    void setIndex(int index);
    void setPattern(juce::BigInteger &b);
    int getIndex();

    juce::BigInteger getPattern();
    void setNote(int noteIndex, bool value);
    bool getNote(int noteIndex);

    static const int maxNumberOfChannels;
    static const int maxNumberOfNotes;

    // State must be public for value tree object list
    juce::ValueTree state;

  private:
    tracktion_engine::ConstrainedCachedValue<int> channelIndex;
    tracktion_engine::ConstrainedCachedValue<juce::String> pattern;
};

} // namespace app_models
