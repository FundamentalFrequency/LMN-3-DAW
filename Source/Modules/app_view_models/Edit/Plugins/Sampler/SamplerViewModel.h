namespace app_view_models
{

    namespace IDs
    {

        const juce::Identifier SAMPLER_VIEW_STATE("SAMPLER_VIEW_STATE");
        const juce::Identifier selectedSoundIndex("selectedSoundIndex");

    }

    class SamplerViewModel
        : public juce::ChangeListener,
          public juce::ValueTree::Listener,
          public app_view_models::ItemListState::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        enum class SamplerType
        {
            SYNTH = 0,
            DRUM = 1
        };

        SamplerViewModel(tracktion_engine::SamplerPlugin* sampler, SamplerType type);
        ~SamplerViewModel();

        juce::StringArray getSampleNames();

        void increaseSelectedIndex();
        void decreaseSelectedIndex();

        void increaseStartTime();
        void decreaseStartTime();

        void increaseEndTime();
        void decreaseEndTime();

        void toggleSamplePlayDirection();

        void setSelectedSoundIndex(int noteNumber);

        void increaseGain();
        void decreaseGain();

        juce::AudioThumbnail& getFullSampleThumbnail();

        double getStartTime();
        double getEndTime();

        double getGain();

        juce::String getSelectedSampleName();

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

        SamplerType samplerType = SamplerType::SYNTH;

        juce::ValueTree state;
        juce::CachedValue<int> selectedSoundIndex;

        juce::StringArray drumKitNames;
        juce::Array<juce::File> mapFiles;
        juce::Array<juce::File> drumSampleFiles;

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

        bool readMappingFileIntoSampler(juce::XmlElement* xml);


    public:
        ItemListState sampleListState;


    };

}



