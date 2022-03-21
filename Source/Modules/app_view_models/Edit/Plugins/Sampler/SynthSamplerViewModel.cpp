#include <SynthSampleData.h>

namespace app_view_models {
    SynthSamplerViewModel::SynthSamplerViewModel(tracktion_engine::SamplerPlugin* sampler)
    : SamplerViewModel(sampler, IDs::SYNTH_SAMPLER_VIEW_STATE) {
        itemListState.listSize = SynthSampleData::namedResourceListSize;

        if (samplerPlugin->getNumSounds() <= 0) {
            const auto destDir = samplerPlugin->edit.getTempDirectory(true);
            const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[0]);
            const auto error = samplerPlugin->addSound(file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0, 0.0, 1.0);
            samplerPlugin->setSoundParams(0, 60, 0, 127);
            samplerPlugin->setSoundGains(0, 1, 0);
            samplerPlugin->setSoundExcerpt(0, 0, tracktion_engine::AudioFile(samplerPlugin->engine, file).getLength());
            selectedSoundIndex.setValue(0, nullptr);
            itemListState.setSelectedItemIndex(0);

            jassert(error.isEmpty());
        }

        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        const auto file = destDir.getChildFile(SynthSampleData::originalFilenames[itemListState.getSelectedItemIndex()]);
        auto* reader = formatManager.createReaderFor(file);
        if (reader != nullptr) {
            // This must be set in order for the plugin state to be loaded in correctly if the sound already existed (ie the number of sounds was > 0)
            samplerPlugin->setSoundMedia(0, file.getFullPathName());

            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            fullSampleThumbnail.clear();
            fullSampleThumbnailCache.clear();
            fullSampleThumbnail.setSource(new juce::FileInputSource(file));
            readerSource.reset(newSource.release());

        }
        markAndUpdate(shouldUpdateSample);
    }


    juce::StringArray SynthSamplerViewModel::getItemNames() {
        juce::StringArray sampleNames;
        const auto destDir = samplerPlugin->edit.getTempDirectory(true);

        for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i) {
            const auto f = destDir.getChildFile(SynthSampleData::originalFilenames[i]);
            sampleNames.add(f.getFileNameWithoutExtension());
        }

        return sampleNames;
    }

    void SynthSamplerViewModel::selectedIndexChanged(int newIndex) {
        const auto destDir = samplerPlugin->edit.getTempDirectory(true);
        auto file = destDir.getChildFile(SynthSampleData::originalFilenames[newIndex]);
        samplerPlugin->setSoundMedia(0, file.getFullPathName());
        samplerPlugin->setSoundParams(0, 60, 0, 127);
        samplerPlugin->setSoundGains(0, 1, 0);
        samplerPlugin->setSoundExcerpt(0, 0, tracktion_engine::AudioFile(samplerPlugin->engine, file).getLength());

        auto* reader = formatManager.createReaderFor(file);
        if (reader != nullptr) {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            fullSampleThumbnail.clear();
            fullSampleThumbnailCache.clear();
            fullSampleThumbnail.setSource(new juce::FileInputSource(file));
            readerSource.reset(newSource.release());
        }

        markAndUpdate(shouldUpdateSample);
    }

}
