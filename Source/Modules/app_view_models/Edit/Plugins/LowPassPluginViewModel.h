#pragma once
namespace app_view_models {
class LowPassPluginViewModel : public juce::ValueTree::Listener,
                               public FlaggedAsyncUpdater {
  public:
    explicit LowPassPluginViewModel(tracktion_engine::LowPassPlugin *p);
    ~LowPassPluginViewModel();

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

        virtual void parametersChanged(){};
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

    juce::NormalisableRange<double> normRange;

  private:
    tracktion_engine::LowPassPlugin *lowPassPlugin;

    juce::ListenerList<Listener> listeners;

    bool shouldUpdateParameters = false;

    void handleAsyncUpdate() override;
};
} // namespace app_view_models
