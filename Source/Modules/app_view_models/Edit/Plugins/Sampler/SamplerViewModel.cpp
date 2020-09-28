#include <SynthSampleData.h>
#include <DrumSampleData.h>
namespace app_view_models
{

    SamplerViewModel::SamplerViewModel(tracktion_engine::SamplerPlugin* sampler, SamplerType type)
        : samplerPlugin(sampler),
          samplerType(type),
          state(samplerPlugin->state.getOrCreateChildWithName(IDs::SAMPLER_VIEW_STATE, nullptr)),
          sampleListState(state, SynthSampleData::namedResourceListSize),
          fullSampleThumbnailCache(5),
          fullSampleThumbnail(numSamplesForThumbnail, formatManager, fullSampleThumbnailCache)
    {

        selectedSoundIndex.referTo(state, IDs::selectedSoundIndex, nullptr, 0);

        if (samplerPlugin->getNumSounds() <= 0)
        {

            const auto destDir = samplerPlugin->edit.getTempDirectory(true);

            if (samplerType == SamplerType::SYNTH)
            {


                const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[0]);
                samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
                samplerPlugin->setSoundParams(0, 60, 0, 127);
                samplerPlugin->setSoundGains(0, 1, 0);


            }

            if (samplerType == SamplerType::DRUM)
            {

                for (int i = 0; i < 24; i++)
                {

                    // add 24 sounds to the sampler (doesnt matter what it is it will be overwritten in the next loop
                    const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[0]);
                    samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
                    samplerPlugin->setSoundParams(0, 60, 0, 127);
                    samplerPlugin->setSoundGains(0, 1, 0);

                }

                // add drum samples to the soun and populate the drum kit list
                for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(destDir,
                                                                                false, "*.xml"))
                {

                    auto xml = juce::parseXML(entry.getFile());
                    if (readMappingFileIntoSampler(xml.get()))
                    {

                       mapFiles.add(entry.getFile());
                       drumKitNames.add(xml->getStringAttribute("kitName"));

                    }

                }

            }

        }

        if (samplerType == SamplerType::SYNTH)
            sampleListState.listSize = SynthSampleData::namedResourceListSize;

        if (samplerType == SamplerType::DRUM)
            sampleListState.listSize = drumKitNames.size();

        formatManager.registerBasicFormats();
        samplerPlugin->state.addListener(this);
        fullSampleThumbnail.addChangeListener(this);
        sampleListState.addListener(this);
        state.addListener(this);

    }

    SamplerViewModel::~SamplerViewModel()
    {

        samplerPlugin->state.removeListener(this);
        sampleListState.removeListener(this);
        state.removeListener(this);
        fullSampleThumbnail.removeChangeListener(this);

    }

    juce::AudioThumbnail& SamplerViewModel::getFullSampleThumbnail()
    {

        return fullSampleThumbnail;

    }

    juce::StringArray SamplerViewModel::getSampleNames()
    {


        if (samplerType == SamplerType::SYNTH)
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

        if (samplerType == SamplerType::DRUM)
        {

            return drumKitNames;

        }

        return juce::StringArray();


    }

    double SamplerViewModel::getStartTime()
    {

        return samplerPlugin->getSoundStartTime(selectedSoundIndex.get());

    }

    double SamplerViewModel::getEndTime()
    {

        return samplerPlugin->getSoundStartTime(selectedSoundIndex.get()) + samplerPlugin->getSoundLength(selectedSoundIndex.get());

    }

    double SamplerViewModel::getGain()
    {

        return samplerPlugin->getSoundGainDb(selectedSoundIndex.get());

    }

    juce::String SamplerViewModel::getSelectedSampleName()
    {

        if (samplerType == SamplerType::SYNTH)
            return getSampleNames()[sampleListState.getSelectedItemIndex()];

        if (samplerType == SamplerType::DRUM)
            return drumSampleFiles[selectedSoundIndex.get()].getFileNameWithoutExtension();

        return {};

    }

    void SamplerViewModel::setSelectedSoundIndex(int noteNumber)
    {

        if (samplerType == SamplerType::DRUM)
            if (noteNumber >= 53 && noteNumber <= 76)
                selectedSoundIndex.setValue(noteNumber - 53, nullptr);

    }


    void SamplerViewModel::selectedIndexChanged(int newIndex)
    {

        if (samplerType == SamplerType::SYNTH)
        {

            const auto destDir = samplerPlugin->edit.getTempDirectory(true);
            auto file = destDir.getChildFile(SynthSampleData::originalFilenames[newIndex]);
            samplerPlugin->setSoundMedia(selectedSoundIndex.get(), file.getFullPathName());
            samplerPlugin->setSoundParams(selectedSoundIndex.get(), 60, 0, 127);
            
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

        if (samplerType == SamplerType::DRUM)
        {

            // we just changed kits
            // reset to sound 0
            selectedSoundIndex.setValue(0, nullptr);
            readMappingFileIntoSampler(juce::parseXML(mapFiles[newIndex]).get());
            auto file = drumSampleFiles[0];
            samplerPlugin->setSoundMedia(selectedSoundIndex.get(), file.getFullPathName());
            samplerPlugin->setSoundParams(selectedSoundIndex.get(), 60, 0, 127);

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


    }

    void SamplerViewModel::increaseSelectedIndex()
    {

        sampleListState.setSelectedItemIndex(sampleListState.getSelectedItemIndex() + 1);

    }

    void SamplerViewModel::decreaseSelectedIndex()
    {

        sampleListState.setSelectedItemIndex(sampleListState.getSelectedItemIndex() - 1);

    }

    void SamplerViewModel::increaseStartTime()
    {

        if (samplerPlugin->getSoundLength(selectedSoundIndex.get()) > 0.0205)
        {

            double start = samplerPlugin->getSoundStartTime(selectedSoundIndex.get()) + .02;
            double length = samplerPlugin->getSoundLength(selectedSoundIndex.get()) - .02;

            samplerPlugin->setSoundExcerpt(selectedSoundIndex.get(), start, length);


        }

    }

    void SamplerViewModel::decreaseStartTime()
    {


        if (samplerPlugin->getSoundStartTime(selectedSoundIndex.get()) > 0)
        {

            double start = samplerPlugin->getSoundStartTime(selectedSoundIndex.get()) - .02;
            if (start <= 0)
                start = 0;

            double length = samplerPlugin->getSoundLength(selectedSoundIndex.get()) + .02;
            samplerPlugin->setSoundExcerpt(selectedSoundIndex.get(), start, length);

        }

    }

    void SamplerViewModel::increaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundStartTime(selectedSoundIndex.get())
                + samplerPlugin->getSoundLength(selectedSoundIndex.get());

        if (currentEnd < samplerPlugin->getSoundFile(selectedSoundIndex.get()).getLength())
        {

            samplerPlugin->setSoundExcerpt(selectedSoundIndex.get(),
                                           samplerPlugin->getSoundStartTime(selectedSoundIndex.get()),
                                           samplerPlugin->getSoundLength(selectedSoundIndex.get()) + .02);

        }

    }

    void SamplerViewModel::decreaseEndTime()
    {

        double currentEnd = samplerPlugin->getSoundStartTime(selectedSoundIndex.get())
                + samplerPlugin->getSoundLength(selectedSoundIndex.get());

        if (currentEnd > samplerPlugin->getSoundStartTime(selectedSoundIndex.get()) + .0205)
        {

            samplerPlugin->setSoundExcerpt(selectedSoundIndex.get(),
                                           samplerPlugin->getSoundStartTime(selectedSoundIndex.get()),
                                           samplerPlugin->getSoundLength(selectedSoundIndex.get()) - .02);

        }

    }

    void SamplerViewModel::toggleSamplePlayDirection()
    {

        // Not sure if there is a way to do this

    }

    void SamplerViewModel::increaseGain()
    {


        samplerPlugin->setSoundGains(selectedSoundIndex.get(),
                                     samplerPlugin->getSoundGainDb(selectedSoundIndex.get()) + 1,
                                     samplerPlugin->getSoundPan(selectedSoundIndex.get()));

    }

    void SamplerViewModel::decreaseGain()
    {

        samplerPlugin->setSoundGains(selectedSoundIndex.get(),
                                     samplerPlugin->getSoundGainDb(selectedSoundIndex.get()) - 1,
                                     samplerPlugin->getSoundPan(selectedSoundIndex.get()));

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

        if (treeWhosePropertyHasChanged == state)
        {

            if (property == IDs::selectedSoundIndex)

            {

                auto file = drumSampleFiles[selectedSoundIndex.get()];

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

    bool SamplerViewModel::readMappingFileIntoSampler(juce::XmlElement*  xml)
    {

        // clear all sounds first
        for (int i = 0; i < samplerPlugin->getNumSounds(); i++)
            samplerPlugin->removeSound(i);

        drumSampleFiles.clear();

        if (xml)
        {
            if (xml->hasTagName("MAPPINGS"))
            {

                if (xml->hasAttribute("kitName"))
                {

                    const auto destDir = samplerPlugin->edit.getTempDirectory(true);
                    bool hasAtLeastOneMapping = false;
                    forEachXmlChildElement(*xml, e)
                    {

                        if (e->hasTagName("MAPPING"))
                        {

                            if (e->getChildByName("NOTE_NUMBER") != nullptr && e->getChildByName("FILE_NAME") != nullptr) {

                                hasAtLeastOneMapping = true;
                                auto noteNumberTag = e->getChildByName("NOTE_NUMBER");
                                auto fileNameTag = e->getChildByName("FILE_NAME");

                                int noteNumber = noteNumberTag->getAllSubText().getIntValue();
                                juce::String fileName = fileNameTag->getAllSubText();

                                const auto file = destDir.getChildFile(fileName);
                                drumSampleFiles.add(file);
                                samplerPlugin->setSoundMedia(drumSampleFiles.size() - 1, file.getFullPathName());
                                samplerPlugin->setSoundParams(drumSampleFiles.size() - 1, noteNumber, noteNumber, noteNumber);
                                samplerPlugin->setSoundGains(drumSampleFiles.size() - 1, 1, 0);
                                samplerPlugin->setSoundExcerpt(drumSampleFiles.size() - 1, 0, tracktion_engine::AudioFile(samplerPlugin->engine, file).getLength());
                                samplerPlugin->setSoundOpenEnded(drumSampleFiles.size() - 1, true);

                            }

                        }

                    }

                    return hasAtLeastOneMapping;

                }

            }

        }

        return false;

    }

}
