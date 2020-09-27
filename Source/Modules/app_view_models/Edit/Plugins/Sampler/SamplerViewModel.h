namespace app_view_models
{

    namespace IDs
    {

        const juce::Identifier SAMPLER_VIEW_STATE("SAMPLER_VIEW_STATE");

    }

    class SamplerViewModel
        : public juce::ChangeListener,
          public juce::ValueTree::Listener,
          public app_view_models::ItemListState::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        SamplerViewModel(tracktion_engine::SamplerPlugin* sampler);
        ~SamplerViewModel();

        juce::StringArray getSampleNames();
        juce::File getSelectedSampleFile();

        void increaseSelectedIndex();
        void decreaseSelectedIndex();

        void increaseStartTime();
        void decreaseStartTime();

        void increaseEndTime();
        void decreaseEndTime();

        void toggleSamplePlayDirection();

        void increaseGain();
        void decreaseGain();

        juce::AudioThumbnail& getFullSampleThumbnail();
        juce::AudioThumbnail& getSampleExcerptThumbnail();

        double getStartTime();
        double getEndTime();

        double getGain();

        void selectedIndexChanged(int newIndex) override;

        void changeListenerCallback(juce::ChangeBroadcaster* source) override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void sampleChanged() {};
            virtual void sampleExcerptTimesChanged() {};
            virtual void fullSampleThumbnailChanged() {};
            virtual void sampleExcerptThumbnailChanged() {};
            virtual void gainChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        const int numSamplesForThumbnail = 512;
        tracktion_engine::SamplerPlugin* samplerPlugin;

        juce::ValueTree state;

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

}



