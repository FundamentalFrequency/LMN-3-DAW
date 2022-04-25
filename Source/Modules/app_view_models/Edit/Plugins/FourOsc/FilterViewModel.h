#pragma once
namespace app_view_models {
class FilterViewModel : public juce::ValueTree::Listener,
                        public FlaggedAsyncUpdater {

  public:
    FilterViewModel(tracktion_engine::FourOscPlugin *p);
    ~FilterViewModel();

    float getAttack() const;
    float getDecay() const;
    float getSustain() const;
    float getRelease() const;
    float getFrequency() const;
    float getResonance() const;
    float getEnvelopeAmount() const;
    int getFilterType() const;

    void incrementAttack();
    void decrementAttack();

    void incrementDecay();
    void decrementDecay();

    void incrementSustain();
    void decrementSustain();

    void incrementRelease();
    void decrementRelease();

    void incrementFrequency();
    void decrementFrequency();

    void incrementResonance();
    void decrementResonance();

    void incrementEnvelopeAmount();
    void decrementEnvelopeAmount();

    void incrementFilterType();
    void decrementFilterType();

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void parametersChanged(){};
    };

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    void addListener(Listener *l);
    void removeListener(Listener *l);

    juce::NormalisableRange<double> filterNormRange;

  private:
    tracktion_engine::FourOscPlugin *plugin;

    juce::ListenerList<Listener> listeners;

    void handleAsyncUpdate() override;
    bool shouldUpdateParameters = false;
};

} // namespace app_view_models
