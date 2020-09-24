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

        formatManager.registerBasicFormats();
        samplerPlugin->state.addListener(this);
        thumbnail.addChangeListener(this);
        itemListState.addListener(this);

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

        // we need to update the thumbnail and the sampler sound
        // clear all sounds first
        for (int i = 0; i < samplerPlugin->getNumSounds(); i++)
            samplerPlugin->removeSound(i);


        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[newIndex]);
        samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
        samplerPlugin->setSoundParams(samplerPlugin->getNumSounds() - 1, 60, 0, 127);

        auto* reader = formatManager.createReaderFor(file);
        if (reader != nullptr)
        {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            thumbnail.setSource(new juce::FileInputSource(file));
            readerSource.reset(newSource.release());

        }

        markAndUpdate(shouldUpdateSample);

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
