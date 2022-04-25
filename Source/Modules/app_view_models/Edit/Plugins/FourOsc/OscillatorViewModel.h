#pragma once
namespace app_view_models {
class OscillatorViewModel : public juce::ValueTree::Listener,
                            public FlaggedAsyncUpdater {

  public:
    OscillatorViewModel(tracktion_engine::FourOscPlugin *p, int oscIndex);
    ~OscillatorViewModel();

    int getWaveShape() const;
    int getVoices() const;
    float getTune() const;
    float getFineTune() const;
    float getLevel() const;
    float getPulseWidth() const;
    float getDetune() const;
    float getSpread() const;
    float getPan() const;

    void incrementWaveShape();
    void decrementWaveShape();

    void incrementVoices();
    void decrementVoices();

    void incrementTune();
    void decrementTune();

    void incrementFineTune();
    void decrementFineTune();

    void incrementLevel();
    void decrementLevel();

    void incrementPulseWidth();
    void decrementPulseWidth();

    void incrementDetune();
    void decrementDetune();

    void incrementSpread();
    void decrementSpread();

    void incrementPan();
    void decrementPan();

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void parametersChanged(){};
    };

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    void addListener(Listener *l);
    void removeListener(Listener *l);

  private:
    tracktion_engine::FourOscPlugin *plugin;
    int oscillatorIndex;

    juce::ListenerList<Listener> listeners;

    void handleAsyncUpdate() override;
    bool shouldUpdateParameters = false;
};

} // namespace app_view_models
