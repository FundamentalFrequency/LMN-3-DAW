#include <SynthSampleData.h>
namespace app_view_models
{

    SamplerViewModel::SamplerViewModel(tracktion_engine::SamplerPlugin* sampler)
        : samplerPlugin(sampler),
          state(samplerPlugin->state.getOrCreateChildWithName(IDs::SAMPLER_VIEW_STATE, nullptr)),
          itemListState(state, SynthSampleData::namedResourceListSize),
          fullSampleThumbnailCache(5),
          fullSampleThumbnail(numSamplesForThumbnail, formatManager, fullSampleThumbnailCache)
    {


        if (samplerPlugin->getNumSounds() <= 0)
        {

            const auto destDir = samplerPlugin->edit.getTempDirectory(true);
            const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[0]);
            samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);

        }


        formatManager.registerBasicFormats();
        samplerPlugin->state.addListener(this);
        fullSampleThumbnail.addChangeListener(this);
        itemListState.addListener(this);


    }

    SamplerViewModel::~SamplerViewModel()
    {

        samplerPlugin->state.removeListener(this);
        itemListState.removeListener(this);
        fullSampleThumbnail.removeChangeListener(this);

    }

    juce::AudioThumbnail& SamplerViewModel::getFullSampleThumbnail()
    {

        return fullSampleThumbnail;

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

    double SamplerViewModel::getStartTime()
    {

        return samplerPlugin->getSoundStartTime(0);

    }

    double SamplerViewModel::getEndTime()
    {

        return samplerPlugin->getSoundStartTime(0) + samplerPlugin->getSoundLength(0);

    }

    double SamplerViewModel::getGain()
    {

        return samplerPlugin->getSoundGainDb(0);

    }

    juce::File SamplerViewModel::getSelectedSampleFile()
    {

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        return destDir.getChildFile(SynthSampleData::originalFilenames[itemListState.getSelectedItemIndex()]);

    }

    void SamplerViewModel::selectedIndexChanged(int newIndex)
    {

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        auto file = destDir.getChildFile(SynthSampleData::originalFilenames[newIndex]);
        samplerPlugin->setSoundMedia(0, file.getFullPathName());
        samplerPlugin->setSoundParams(0, 60, 0, 127);
        samplerPlugin->setSoundGains(0, 1, 0);

        auto* reader = formatManager.createReaderFor(file);
        if (reader != nullptr)
        {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            fullSampleThumbnail.clear();
            fullSampleThumbnailCache.clear();
            fullSampleThumbnail.setSource(new juce::FileInputSource(file));
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


        if (samplerPlugin->getSoundStartTime(0) > 0)
        {

            double start = samplerPlugin->getSoundStartTime(0) - .02;
            if (start <= 0)
                start = 0;

            double length = samplerPlugin->getSoundLength(0) + .02;
            samplerPlugin->setSoundExcerpt(0, start, length);

        }

    }

    void SamplerViewModel::increaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundStartTime(0) + samplerPlugin->getSoundLength(0);

        if (currentEnd < samplerPlugin->getSoundFile(0).getLength())
        {

            samplerPlugin->setSoundExcerpt(0, samplerPlugin->getSoundStartTime(0), samplerPlugin->getSoundLength(0) + .02);

        }

    }

    void SamplerViewModel::decreaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundStartTime(0) + samplerPlugin->getSoundLength(0);

        if (currentEnd > samplerPlugin->getSoundStartTime(0) + .0205)
        {

            samplerPlugin->setSoundExcerpt(0, samplerPlugin->getSoundStartTime(0), samplerPlugin->getSoundLength(0) - .02);

        }

    }

    void SamplerViewModel::toggleSamplePlayDirection()
    {

        // Not sure if there is a way to do this
        // Below does not work and its the only thing I could think to try
//        if (samplerPlugin->getSoundLength(0) >= 0)
//        {
//
//            // length is positive, need to set the start time to be the current end time,
//            // and the length to be negative
//            double currentEnd = samplerPlugin->getSoundStartTime(0) + samplerPlugin->getSoundLength(0);
//            double currentLength = samplerPlugin->getSoundLength(0);
//            samplerPlugin->setSoundExcerpt(0, currentEnd, -1 * currentLength);
//
//
//        }
//        else
//        {
//
//            // length is negative, need to set the start time to be the current start + current length (length is -)
//            // and set length to be positive
//            double currentStart = samplerPlugin->getSoundStartTime(0);
//            double currentLength = samplerPlugin->getSoundLength(0);
//            samplerPlugin->setSoundExcerpt(0, currentStart + currentLength, -1 * currentLength);
//
//        }


    }

    void SamplerViewModel::increaseGain()
    {


        samplerPlugin->setSoundGains(0, samplerPlugin->getSoundGainDb(0) + 1, samplerPlugin->getSoundPan(0));

    }

    void SamplerViewModel::decreaseGain()
    {

        samplerPlugin->setSoundGains(0, samplerPlugin->getSoundGainDb(0) - 1, samplerPlugin->getSoundPan(0));

    }


    void SamplerViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSample))
            listeners.call([this](Listener &l) { l.sampleChanged(); });

        if (compareAndReset(shouldUpdateFullSampleThumbnail))
            listeners.call([this](Listener &l) { l.fullSampleThumbnailChanged(); });

        if (compareAndReset(shouldUpdateSampleExcerptTimes))
            listeners.call([this](Listener &l) { l.sampleExcerptTimesChanged(); });

        if (compareAndReset(shouldUpdateGain))
            listeners.call([this](Listener &l) { l.gainChanged(); });


    }

    void SamplerViewModel::changeListenerCallback(juce::ChangeBroadcaster* source)
    {

        if (source == &fullSampleThumbnail)
            markAndUpdate(shouldUpdateFullSampleThumbnail);


    }

    void SamplerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged.hasType(tracktion_engine::IDs::SOUND))
        {

            markAndUpdate(shouldUpdateSampleExcerptTimes);
            if (property == tracktion_engine::IDs::gainDb)
                markAndUpdate(shouldUpdateGain);

        }


    }

    void SamplerViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->sampleChanged();
        l->gainChanged();

    }

    void SamplerViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);

    }



}
