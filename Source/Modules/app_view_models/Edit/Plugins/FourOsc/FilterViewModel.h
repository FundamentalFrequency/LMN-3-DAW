#pragma once
namespace app_view_models {
class FilterViewModel : public juce::ValueTree::Listener,
                        public FlaggedAsyncUpdater {
  public:
    FilterViewModel(tracktion::FourOscPlugin *p);
    ~FilterViewModel() override;

    float getAttack() const;
    float getDecay() const;
    float getSustain() const;
    float getRelease() const;
    float getFrequency() const;
    juce::Range<float> getFrequencyRange() const;
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

        virtual void parametersChanged() {}
    };

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    void addListener(Listener *l);
    void removeListener(Listener *l);

    juce::NormalisableRange<double> filterNormRange;

  private:
    tracktion::FourOscPlugin *plugin;

    juce::ListenerList<Listener> listeners;

    void handleAsyncUpdate() override;
    static float convertMidiNoteToHz(float noteNumber);
    bool shouldUpdateParameters = false;
};

} // namespace app_view_models
