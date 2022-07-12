namespace app_view_models {
SynthSamplerViewModel::SynthSamplerViewModel(tracktion::SamplerPlugin *sampler)
    : SamplerViewModel(sampler, IDs::SYNTH_SAMPLER_VIEW_STATE) {
    curDir = ConfigurationHelpers::getTempSamplesDirectory(
        samplerPlugin->edit.engine);

    updateFiles();

    itemListState.listSize = files.size();

    curFile = curDir.findChildFiles(juce::File::TypesOfFileToFind::findFiles,
                                    false)[0];

    int curIndex = files.indexOf(curFile);

    if (samplerPlugin->getNumSounds() <= 0) {
        const auto error = samplerPlugin->addSound(
            curFile.getFullPathName(), curFile.getFileNameWithoutExtension(),
            0.0, 0.0, 1.0);
        samplerPlugin->setSoundParams(0, 60, 0, 127);
        samplerPlugin->setSoundGains(0, 1, 0);
        samplerPlugin->setSoundExcerpt(
            0, 0,
            tracktion::AudioFile(samplerPlugin->engine, curFile).getLength());
        selectedSoundIndex.setValue(0, nullptr);
        itemListState.setSelectedItemIndex(curIndex);

        jassert(error.isEmpty());
    }

    auto *reader = formatManager.createReaderFor(curFile);
    if (reader != nullptr) {
        // This must be set in order for the plugin state to be loaded in
        // correctly if the sound already existed (ie the number of sounds was >
        // 0)
        samplerPlugin->setSoundMedia(selectedSoundIndex.get(),
                                     curFile.getFullPathName());

        std::unique_ptr<juce::AudioFormatReaderSource> newSource(
            new juce::AudioFormatReaderSource(reader, true));
        fullSampleThumbnail.clear();
        fullSampleThumbnailCache.clear();
        fullSampleThumbnail.setSource(new juce::FileInputSource(curFile));
        readerSource.reset(newSource.release());
    }
    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::updateFiles() {
    files.clear();
    // auto dirs =
    //     curDir.findChildFiles(juce::File::TypesOfFileToFind::findDirectories,
    //     false);
    // auto files =
    //     curDir.findChildFiles(juce::File::TypesOfFileToFind::findFiles,
    //     false);
    auto sampleDir = ConfigurationHelpers::getTempSamplesDirectory(
        samplerPlugin->edit.engine);
    if (curDir.isAChildOf(sampleDir)) {
        auto parent = curDir.getChildFile("..");
        files.add(parent);
    }
    // for (const auto &dir : dirs) {
    //     curItemNames.add(dir);
    // }
    // for (const auto &file : files) {
    //     curItemNames.add(file);
    // }
    // itemNames = curItemNames;
    files.addArray(curDir.findChildFiles(
        juce::File::TypesOfFileToFind::findFilesAndDirectories, false));
}

juce::StringArray SynthSamplerViewModel::getItemNames() {
    juce::StringArray itemNames;
    for (const juce::File &file : files) {
        if (file.isDirectory()) {
            if (curDir.isAChildOf(file)) {
                itemNames.add("..");
            } else {
                itemNames.add(file.getFileNameWithoutExtension() + "/");
            }
        } else {
            itemNames.add(file.getFileNameWithoutExtension());
        }
    }
    return itemNames;
}

juce::String SynthSamplerViewModel::getTitle() {
    auto title = curDir.getFileNameWithoutExtension(); // TODO
    return curDir.getFileNameWithoutExtension();
}

bool SynthSamplerViewModel::isDir() { return curFile.isDirectory(); }

void SynthSamplerViewModel::enterDir() {
    if (!isDir()) {
        return;
    }
    curDir = curFile;
    updateFiles();
    itemListState.listSize = files.size();
    itemListState.setSelectedItemIndex(0);
    selectedIndexChanged(0);
}

void SynthSamplerViewModel::selectedIndexChanged(int newIndex) {
    curFile = files[newIndex];
    if (!curFile.isDirectory()) {
        samplerPlugin->setSoundMedia(0, curFile.getFullPathName());
        samplerPlugin->setSoundParams(0, 60, 0, 127);
        samplerPlugin->setSoundGains(0, 1, 0);
        samplerPlugin->setSoundExcerpt(
            0, 0,
            tracktion::AudioFile(samplerPlugin->engine, curFile).getLength());

        auto *reader = formatManager.createReaderFor(curFile);
        if (reader != nullptr) {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(
                new juce::AudioFormatReaderSource(reader, true));
            fullSampleThumbnail.clear();
            fullSampleThumbnailCache.clear();
            fullSampleThumbnail.setSource(new juce::FileInputSource(curFile));
            readerSource.reset(newSource.release());
        }
    }

    markAndUpdate(shouldUpdateSample);
}

} // namespace app_view_models
