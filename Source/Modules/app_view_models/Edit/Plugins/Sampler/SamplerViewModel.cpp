#include <SynthSampleData.h>
namespace app_view_models
{

    SamplerViewModel::SamplerViewModel(tracktion_engine::SamplerPlugin* sampler)
        : samplerPlugin(sampler),
          state(samplerPlugin->state.getOrCreateChildWithName(IDs::SAMPLER_VIEW_STATE, nullptr)),
          itemListState(state, SynthSampleData::namedResourceListSize),
          thumbnailCache(5),
          thumbnail(512, formatManager, thumbnailCache)
    {


        if (samplerPlugin->getNumSounds() <= 0)
        {

            const auto destDir = samplerPlugin->edit.getTempDirectory(true);
            const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[0]);
            samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);

        }


        formatManager.registerBasicFormats();
        samplerPlugin->state.addListener(this);
        thumbnail.addChangeListener(this);
        itemListState.addListener(this);




    }

    SamplerViewModel::~SamplerViewModel()
    {

        samplerPlugin->state.removeListener(this);
        itemListState.removeListener(this);
        thumbnail.removeChangeListener(this);

    }

    juce::AudioThumbnail& SamplerViewModel::getThumbnail()
    {

        return thumbnail;

    }

    juce::StringArray SamplerViewModel::getSampleNames()
    {
        juce::StringArray sampleNames;

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);

        for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i)
        {
            const auto f = destDir.getChildFile(SynthSampleData::originalFilenames[i]);
            sampleNames.add(f.getFileNameWithoutExtension());

        }

        return sampleNames;

    }

    juce::File SamplerViewModel::getSelectedSampleFile()
    {

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        return destDir.getChildFile(SynthSampleData::originalFilenames[itemListState.getSelectedItemIndex()]);

    }

    void SamplerViewModel::selectedIndexChanged(int newIndex)
    {

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[newIndex]);
        samplerPlugin->setSoundMedia(0, file.getFullPathName());
        samplerPlugin->setSoundParams(0, 60, 0, 127);

        auto* reader = formatManager.createReaderFor(file);
        if (reader != nullptr)
        {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            thumbnail.setSource(new juce::FileInputSource(file));
            readerSource.reset(newSource.release());

        }

        markAndUpdate(shouldUpdateSample);

    }

    void SamplerViewModel::increaseSelectedIndex()
    {

        itemListState.setSelectedItemIndex(itemListState.getSelectedItemIndex() + 1);

    }

    void SamplerViewModel::decreaseSelectedIndex()
    {

        itemListState.setSelectedItemIndex(itemListState.getSelectedItemIndex() - 1);

    }

    void SamplerViewModel::increaseStartTime()
    {

        if (samplerPlugin->getSoundLength(0) > 0.0205)
        {

            double start = samplerPlugin->getSoundStartTime(0) + .02;
            double length = samplerPlugin->getSoundLength(0) - .02;
            samplerPlugin->setSoundExcerpt(0, start, length);

        }

    }

    void SamplerViewModel::decreaseStartTime()
    {


        if (samplerPlugin->getSoundStartTime(0) > 0.0205)
        {

            double start = samplerPlugin->getSoundStartTime(0) - .02;
            double length = samplerPlugin->getSoundLength(0) + .02;
            samplerPlugin->setSoundExcerpt(0, start, length);

        }

    }

    void SamplerViewModel::increaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundLength(0) - samplerPlugin->getSoundStartTime(0);

        if (currentEnd < samplerPlugin->getSoundFile(0).getLength())
        {

            samplerPlugin->setSoundExcerpt(0, samplerPlugin->getSoundStartTime(0), samplerPlugin->getSoundLength(0) + .02);

        }

    }

    void SamplerViewModel::decreaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundLength(0) + samplerPlugin->getSoundStartTime(0);

        if (currentEnd > .0205)
        {

            samplerPlugin->setSoundExcerpt(0, samplerPlugin->getSoundStartTime(0), samplerPlugin->getSoundLength(0) - .02);

        }

    }


    void SamplerViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSample))
            listeners.call([this](Listener &l) { l.sampleChanged(); });;


    }

    void SamplerViewModel::changeListenerCallback(juce::ChangeBroadcaster* source)
    {

        if (source == &thumbnail)
            markAndUpdate(shouldUpdateSample);

    }

    void SamplerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged.hasType(tracktion_engine::IDs::SOUND))
            markAndUpdate(shouldUpdateSample);

    }

    void SamplerViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->sampleChanged();

    }

    void SamplerViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);

    }



}
