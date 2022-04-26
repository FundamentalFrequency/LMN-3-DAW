
namespace app_models {

namespace IDs {

const juce::Identifier STEP_SEQUENCE("STEP_SEQUENCE");

}
class StepSequence {
  public:
    explicit StepSequence(juce::ValueTree v);

    StepChannel *getChannel(int index);

  private:
    juce::ValueTree state;
    StepChannelList channelList;
};

} // namespace app_models
