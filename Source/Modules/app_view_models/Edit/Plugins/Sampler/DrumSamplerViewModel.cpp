#include <DrumSampleData.h>

namespace app_view_models
{

    DrumSamplerViewModel:: DrumSamplerViewModel(internal_plugins::DrumSamplerPlugin* sampler)
            : SamplerViewModel(sampler, IDs::DRUM_SAMPLER_VIEW_STATE)
    {


        updateDrumKits();
        itemListState.listSize = drumKitNames.size();


        // if the sampler has no sounds, we need to load the current kit into it
        // if it already has sounds, that means we just need to reload the sample files for the current kit
        if (samplerPlugin->getNumSounds() <= 0)
            readMappingFileIntoSampler(juce::parseXML(mapFiles[itemListState.getSelectedItemIndex()]).get());
        else
            updateSampleFilesForCurrentKit();

        updateThumb();

    }

    juce::StringArray DrumSamplerViewModel::getItemNames()
    {

        return drumKitNames;

    }

    juce::String DrumSamplerViewModel::getSelectedItemName()
    {

        return drumSampleFiles[selectedSoundIndex].getFileNameWithoutExtension();

    }


    void DrumSamplerViewModel::setSelectedSoundIndex(int noteNumber)
    {

        if (noteNumber >= 53 && noteNumber <= 76)
            selectedSoundIndex.setValue(noteNumber - 53, nullptr);

    }


    void DrumSamplerViewModel::selectedIndexChanged(int newIndex)
    {

        // we just changed kits
        readMappingFileIntoSampler(juce::parseXML(mapFiles[newIndex]).get());
        selectedSoundIndex.setValue(0, nullptr);
        markAndUpdate(shouldUpdateGain);        updateThumb();

    }



    void DrumSamplerViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        SamplerViewModel::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);

        if (treeWhosePropertyHasChanged == state)
        {

            if (property == IDs::selectedSoundIndex)
            {

                markAndUpdate(shouldUpdateGain);
                updateThumb();

            }

        }

    }

    void DrumSamplerViewModel::readMappingFileIntoSampler(juce::XmlElement*  xml)
    {

        drumSampleFiles.clear();
        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        forEachXmlChildElement(*xml, e)
        {

            auto noteNumberTag = e->getChildByName("NOTE_NUMBER");
            auto fileNameTag = e->getChildByName("FILE_NAME");

            int noteNumber = noteNumberTag->getAllSubText().getIntValue();
            juce::String fileName = fileNameTag->getAllSubText();

            const auto file = destDir.getChildFile(fileName);
            drumSampleFiles.add(file);

            // check if the drum sampler has enough sounds to cover this index:
            // if it doesnt have enough sounds we need to add one
            // otherwise just change the sound media
            int index = drumSampleFiles.size() - 1;
            if (samplerPlugin->getNumSounds() <= index)
            {

                juce::String error = samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
                jassert(error.isEmpty());

            }
            else
            {

                samplerPlugin->setSoundMedia(index, file.getFullPathName());

            }

            samplerPlugin->setSoundParams(index, noteNumber, noteNumber, noteNumber);
            samplerPlugin->setSoundGains(index, 1, 0);
            samplerPlugin->setSoundExcerpt(index, 0, tracktion_engine::AudioFile(samplerPlugin->engine, file).getLength());
            samplerPlugin->setSoundOpenEnded(index, true);

        }


    }

    void DrumSamplerViewModel::updateDrumKits() {


        mapFiles.clear();
        drumKitNames.clear();

        // add drum samples to the sound and populate the drum kit list
        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(destDir,
                                                                        false, "*.xml")) {

            auto xml = juce::parseXML(entry.getFile());

            if (isMapValid(xml.get())) {

                DBG("Valid drum sampler map found: " + xml->getStringAttribute("kitName"));
                drumKitNames.add(xml->getStringAttribute("kitName"));
                mapFiles.add(entry.getFile());

            }

        }

    }

    bool DrumSamplerViewModel::isMapValid(juce::XmlElement* xml)
    {

        if (xml) {
            if (xml->hasTagName("MAPPINGS"))
            {

                if (xml->hasAttribute("kitName"))
                {

                    const auto destDir = samplerPlugin->edit.getTempDirectory(true);
                    forEachXmlChildElement(*xml, e)
                    {

                        if (e->hasTagName("MAPPING"))
                        {

                            if (e->getChildByName("NOTE_NUMBER") == nullptr ||
                                e->getChildByName("FILE_NAME") == nullptr)
                            {

                                return false;

                            }

                        }
                        else
                        {

                            return false;
                        }


                    }

                    return true;

                }
                else
                {

                    return false;
                }

            }
            else
            {
                return false;

            }

        }
        else
        {

            return false;
        }


    }

    void DrumSamplerViewModel::updateThumb()
    {

        auto file = drumSampleFiles[selectedSoundIndex];

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

    void DrumSamplerViewModel::updateSampleFilesForCurrentKit()
    {

        drumSampleFiles.clear();
        const auto destDir = samplerPlugin->edit.getTempDirectory(true);

        juce::File currentMap = mapFiles[itemListState.getSelectedItemIndex()];
        auto xml = juce::parseXML(currentMap);
        forEachXmlChildElement(*xml, e)
        {

            auto fileNameTag = e->getChildByName("FILE_NAME");
            juce::String fileName = fileNameTag->getAllSubText();
            const auto file = destDir.getChildFile(fileName);
            drumSampleFiles.add(file);


        }

    }

}
