namespace app_view_models {

namespace IDs {

const juce::Identifier selectedSoundIndex("selectedSoundIndex");

}

class SamplerViewModel : public juce::ChangeListener,
                         public juce::ValueTree::Listener,
                         public app_view_models::ItemListState::Listener,
                         public FlaggedAsyncUpdater {

  public:
    explicit SamplerViewModel(tracktion_engine::SamplerPlugin *sampler,
                              juce::Identifier stateIdentifier);
    ~SamplerViewModel();

    virtual juce::StringArray getItemNames() = 0;

    virtual void setSelectedSoundIndex(int noteNumber){};

    void increaseSelectedIndex();
    void decreaseSelectedIndex();

    void increaseStartTime();
    void decreaseStartTime();

    void increaseEndTime();
    void decreaseEndTime();

    void toggleSamplePlayDirection();

    void increaseGain();
    void decreaseGain();

    juce::AudioThumbnail &getFullSampleThumbnail();

    double getStartTime();
    double getEndTime();

    double getGain();

    virtual juce::String getSelectedItemName();

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void sampleChanged(){};
        virtual void sampleExcerptTimesChanged(){};
        virtual void fullSampleThumbnailChanged(){};
        virtual void sampleExcerptThumbnailChanged(){};
        virtual void gainChanged(){};
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

  protected:
    const int numSamplesForThumbnail = 512;
    tracktion_engine::SamplerPlugin *samplerPlugin;

    juce::ValueTree state;
    juce::CachedValue<int> selectedSoundIndex;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    juce::AudioThumbnailCache fullSampleThumbnailCache;
    juce::AudioThumbnail fullSampleThumbnail;

    juce::ListenerList<Listener> listeners;

    bool shouldUpdateFullSampleThumbnail = false;
    bool shouldUpdateSampleExcerptTimes = false;
    bool shouldUpdateSample = false;
    bool shouldUpdateGain = false;

    void handleAsyncUpdate() override;

  public:
    ItemListState itemListState;
};

} // namespace app_view_models
