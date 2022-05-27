namespace app_view_models {
SynthSamplerViewModel::SynthSamplerViewModel(
    tracktion_engine::SamplerPlugin *sampler)
    : SamplerViewModel(sampler, IDs::SYNTH_SAMPLER_VIEW_STATE) {
    const auto samplesDir = ConfigurationHelpers::getTempSamplesDirectory(
        samplerPlugin->edit.engine);
    itemListState.listSize = samplesDir.getNumberOfChildFiles(
        juce::File::TypesOfFileToFind::findFiles);

    auto files = samplesDir.findChildFiles(
        juce::File::TypesOfFileToFind::findFiles, false);

    if (samplerPlugin->getNumSounds() <= 0) {
        const auto file = files[0];
        const auto error = samplerPlugin->addSound(
            file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0,
            0.0, 1.0);
        samplerPlugin->setSoundParams(0, 60, 0, 127);
        samplerPlugin->setSoundGains(0, 1, 0);
        samplerPlugin->setSoundExcerpt(
            0, 0,
            tracktion_engine::AudioFile(samplerPlugin->engine, file)
                .getLength());
        selectedSoundIndex.setValue(0, nullptr);
        itemListState.setSelectedItemIndex(0);

        jassert(error.isEmpty());
    }

    const auto file = files[0];
    auto *reader = formatManager.createReaderFor(file);
    if (reader != nullptr) {
        // This must be set in order for the plugin state to be loaded in
        // correctly if the sound already existed (ie the number of sounds was >
        // 0)
        samplerPlugin->setSoundMedia(0, file.getFullPathName());

        std::unique_ptr<juce::AudioFormatReaderSource> newSource(
            new juce::AudioFormatReaderSource(reader, true));
        fullSampleThumbnail.clear();
        fullSampleThumbnailCache.clear();
        fullSampleThumbnail.setSource(new juce::FileInputSource(file));
        readerSource.reset(newSource.release());
    }
    markAndUpdate(shouldUpdateSample);
}

juce::StringArray SynthSamplerViewModel::getItemNames() {
    juce::StringArray sampleNames;
    const auto destDir =
        samplerPlugin->edit.engine.getTemporaryFileManager().getTempFile(
            ConfigurationHelpers::SAMPLES_DIRECTORY_NAME);
    auto files =
        destDir.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false);
    for (const auto &file : files) {
        sampleNames.add(file.getFileNameWithoutExtension());
    }

    return sampleNames;
}

void SynthSamplerViewModel::selectedIndexChanged(int newIndex) {
    const auto destDir =
        samplerPlugin->edit.engine.getTemporaryFileManager().getTempFile(
            ConfigurationHelpers::SAMPLES_DIRECTORY_NAME);
    auto files =
        destDir.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false);
    auto file = files[newIndex];
    samplerPlugin->setSoundMedia(0, file.getFullPathName());
    samplerPlugin->setSoundParams(0, 60, 0, 127);
    samplerPlugin->setSoundGains(0, 1, 0);
    samplerPlugin->setSoundExcerpt(
        0, 0,
        tracktion_engine::AudioFile(samplerPlugin->engine, file).getLength());

    auto *reader = formatManager.createReaderFor(file);
    if (reader != nullptr) {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(
            new juce::AudioFormatReaderSource(reader, true));
        fullSampleThumbnail.clear();
        fullSampleThumbnailCache.clear();
        fullSampleThumbnail.setSource(new juce::FileInputSource(file));
        readerSource.reset(newSource.release());
    }

    markAndUpdate(shouldUpdateSample);
}

} // namespace app_view_models
