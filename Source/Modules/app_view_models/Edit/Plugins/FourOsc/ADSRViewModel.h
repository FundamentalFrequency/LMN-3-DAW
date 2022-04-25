#pragma once
namespace app_view_models {
class ADSRViewModel : public juce::ValueTree::Listener,
                      public FlaggedAsyncUpdater {

  public:
    ADSRViewModel(tracktion_engine::FourOscPlugin *p);
    ~ADSRViewModel();

    float getAttack() const;
    float getDecay() const;
    float getSustain() const;
    float getRelease() const;

    void incrementAttack();
    void decrementAttack();

    void incrementDecay();
    void decrementDecay();

    void incrementSustain();
    void decrementSustain();

    void incrementRelease();
    void decrementRelease();

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

    juce::ListenerList<Listener> listeners;

    void handleAsyncUpdate() override;
    bool shouldUpdateParameters = false;
};

} // namespace app_view_models
