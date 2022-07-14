namespace app_view_models {
SynthSamplerViewModel::SynthSamplerViewModel(tracktion::SamplerPlugin *sampler)
    : SamplerViewModel(sampler, IDs::SYNTH_SAMPLER_VIEW_STATE) {
    curFilePath.referTo(state, IDs::curFilePathID, nullptr, "");

    auto curFile = juce::File(curFilePath);

    if (curFile == juce::String{""}) {
        // fist time initialization
        curDir = ConfigurationHelpers::getTempSamplesDirectory(
            samplerPlugin->edit.engine);
        curFile = curDir.findChildFiles(
            juce::File::TypesOfFileToFind::findFiles, false)[0];
        curFilePath.setValue(curFile.getFullPathName(), nullptr);
    } else if (curFile.isDirectory()) {
        // curFile should never be a directory, but just in case
        curDir = curFile;
        curFile = curDir.findChildFiles(
            juce::File::TypesOfFileToFind::findFiles, false)[0];
        curFilePath.setValue(curFile.getFullPathName(), nullptr);
    } else {
        curDir = curFile.getParentDirectory();
    }

    // if (curFile != juce::String{""})
    // {
    //     samplerPlugin->setSoundMedia(0, curFile.getFullPathName());
    // }
    updateThumb();

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
        juce::File::TypesOfFileToFind::findDirectories, false));
    files.addArray(
        curDir.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false));
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
    auto curFile = juce::File(curFilePath);
    if (curFile.isDirectory() || curFile == juce::String{""}) {
        return juce::String{"Select a sample!"};
    } else {
        return curFile.getFileNameWithoutExtension();
    }
}

juce::String SynthSamplerViewModel::getTitle() {
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

void SynthSamplerViewModel::updateThumb() {
    auto curFile = juce::File(curFilePath);
    auto *reader = formatManager.createReaderFor(curFile);
    if (reader != nullptr) {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(
            new juce::AudioFormatReaderSource(reader, true));
        fullSampleThumbnail.clear();
        fullSampleThumbnailCache.clear();
        fullSampleThumbnail.setSource(new juce::FileInputSource(curFile));
        readerSource.reset(newSource.release());
    }

    markAndUpdate(shouldUpdateFullSampleThumbnail);
}

void SynthSamplerViewModel::fileChanged() {
    auto curFile = juce::File(curFilePath);
    if (curFile == juce::String{""}) {
        return;
    }

    if (samplerPlugin->getNumSounds() <= 0) {
        const auto error = samplerPlugin->addSound(
            curFile.getFullPathName(), curFile.getFileNameWithoutExtension(),
            0.0, 0.0, 1.0);
        jassert(error.isEmpty());
    }

    samplerPlugin->setSoundMedia(0, curFile.getFullPathName());
    samplerPlugin->setSoundParams(0, 60, 0, 127);
    samplerPlugin->setSoundGains(0, 1, 0);
    samplerPlugin->setSoundExcerpt(
        0, 0, tracktion::AudioFile(samplerPlugin->engine, curFile).getLength());

    updateThumb();

    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::selectedIndexChanged(int newIndex) {
    nextFile = files[newIndex];
    if (!nextFile.isDirectory()) {
        curFilePath.setValue(nextFile.getFullPathName(), nullptr);
    }
    markAndUpdate(shouldUpdateSample);
}

void SynthSamplerViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    SamplerViewModel::valueTreePropertyChanged(treeWhosePropertyHasChanged,
                                               property);
    if (treeWhosePropertyHasChanged == state) {
        if (property == IDs::curFilePathID) {
            fileChanged();
        }
    }
}

} // namespace app_view_models
