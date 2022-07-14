namespace app_view_models {
SynthSamplerViewModel::SynthSamplerViewModel(tracktion::SamplerPlugin *sampler)
    : SamplerViewModel(sampler, IDs::SYNTH_SAMPLER_VIEW_STATE),
      curFileState(state, 100) {
    auto curFile = curFileState.getFile();

    if (curFile == juce::String{""}) {
        // fist time initialization
        curDir = ConfigurationHelpers::getTempSamplesDirectory(
            samplerPlugin->edit.engine);
        curFile = curDir.findChildFiles(
            juce::File::TypesOfFileToFind::findFiles, false)[0];
        curFileState.setFile(curFile);
    } else if (curFile.isDirectory()) {
        // curFile should never be a directory, but just in case
        curDir = curFile;
        curFile = curDir.findChildFiles(
            juce::File::TypesOfFileToFind::findFiles, false)[0];
        curFileState.setFile(curFile);
    } else {
        curDir = curFile.getParentDirectory();
    }

    curFileState.addListener(this);

    updateFiles();
    itemListState.listSize = files.size();
    int curIndex = files.indexOf(curFile);
    itemListState.setSelectedItemIndex(curIndex);

    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::updateFiles() {
    files.clear();
    auto sampleDir = ConfigurationHelpers::getTempSamplesDirectory(
        samplerPlugin->edit.engine);
    if (curDir.isAChildOf(sampleDir)) {
        auto parent = curDir.getChildFile("..");
        files.add(parent);
    }
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

juce::String SynthSamplerViewModel::getSelectedItemName() {
    auto curFile = curFileState.getFile();
    if (curFile.isDirectory() || curFile == juce::String{""}) {
        return juce::String{"Select a sample!"};
    } else {
        return curFileState.getFile().getFileNameWithoutExtension();
    }
}

juce::String SynthSamplerViewModel::getTitle() {
    auto title = curDir.getFileNameWithoutExtension(); // TODO
    return curDir.getFileNameWithoutExtension();
}

bool SynthSamplerViewModel::isDir() { return nextFile.isDirectory(); }

void SynthSamplerViewModel::enterDir() {
    if (!isDir()) {
        return;
    }
    curDir = nextFile;
    updateFiles();
    itemListState.listSize = files.size();
    itemListState.setSelectedItemIndex(0);
    selectedIndexChanged(0);

    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::fileChanged(juce::File newFile) {
    if (newFile == juce::String{""}) {
        return;
    }

    if (samplerPlugin->getNumSounds() <= 0) {
        const auto error = samplerPlugin->addSound(
            newFile.getFullPathName(), newFile.getFileNameWithoutExtension(),
            0.0, 0.0, 1.0);
        jassert(error.isEmpty());
    }

    samplerPlugin->setSoundMedia(0, newFile.getFullPathName());
    samplerPlugin->setSoundParams(0, 60, 0, 127);
    samplerPlugin->setSoundGains(0, 1, 0);
    samplerPlugin->setSoundExcerpt(
        0, 0, tracktion::AudioFile(samplerPlugin->engine, newFile).getLength());

    auto *reader = formatManager.createReaderFor(newFile);
    if (reader != nullptr) {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(
            new juce::AudioFormatReaderSource(reader, true));
        fullSampleThumbnail.clear();
        fullSampleThumbnailCache.clear();
        fullSampleThumbnail.setSource(new juce::FileInputSource(newFile));
        readerSource.reset(newSource.release());
    }

    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::selectedIndexChanged(int newIndex) {
    nextFile = files[newIndex];
    if (!nextFile.isDirectory()) {
        curFileState.setFile(nextFile);
    }
    markAndUpdate(shouldUpdateSample);
}

} // namespace app_view_models
