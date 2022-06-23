#pragma once
namespace app_view_models {
class LowPassPluginViewModel : public juce::ValueTree::Listener,
                               public FlaggedAsyncUpdater {
  public:
    explicit LowPassPluginViewModel(tracktion::LowPassPlugin *p);
    ~LowPassPluginViewModel() override;

    double getFrequency();
    void setFrequency(double freq);
    juce::Range<double> getFrequencyRange();
    int getFrequencyInterval();

    void incrementFrequency();
    void decrementFrequency();

    void setIsLowPass(bool isLowPass);
    bool getIsLowPass();
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void parametersChanged() {}
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

    juce::NormalisableRange<double> normRange;

  private:
    tracktion::LowPassPlugin *lowPassPlugin;

    juce::ListenerList<Listener> listeners;

    bool shouldUpdateParameters = false;

    void handleAsyncUpdate() override;
};
} // namespace app_view_models
