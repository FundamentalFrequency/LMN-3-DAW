namespace app_models {
class StepChannelList
    : public tracktion_engine::ValueTreeObjectList<StepChannel> {
  public:
    explicit StepChannelList(const juce::ValueTree &v);

    ~StepChannelList();

    bool isSuitableType(const juce::ValueTree &v) const override;

    StepChannel *createNewObject(const juce::ValueTree &v) override;

    void deleteObject(StepChannel *t) override;

    void newObjectAdded(StepChannel *t) override;

    void objectRemoved(StepChannel *t) override;

    void objectOrderChanged() override;
};

} // namespace app_models
