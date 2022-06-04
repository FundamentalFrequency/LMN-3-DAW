
namespace app_view_models {

DrumSamplerViewModel::DrumSamplerViewModel(
    internal_plugins::DrumSamplerPlugin *sampler)
    : SamplerViewModel(sampler, IDs::DRUM_SAMPLER_VIEW_STATE) {
    updateDrumKits();
    itemListState.listSize = drumKitNames.size();

    if (drumKitNames.size() > 0) {
        DBG("current kit index: " +
            std::to_string(itemListState.getSelectedItemIndex()));
        juce::File currentMap = mapFiles[itemListState.getSelectedItemIndex()];
        readMappingFileIntoSampler(currentMap, true);
        DBG("updating thumb");
        updateThumb();
    }
}

juce::StringArray DrumSamplerViewModel::getItemNames() { return drumKitNames; }

juce::String DrumSamplerViewModel::getSelectedItemName() {
    return drumSampleFiles[selectedSoundIndex].getFileNameWithoutExtension();
}

void DrumSamplerViewModel::setSelectedSoundIndex(int noteNumber) {
    if (noteNumber >= 53 && noteNumber <= 76)
        selectedSoundIndex.setValue(noteNumber - 53, nullptr);
}

void DrumSamplerViewModel::selectedIndexChanged(int newIndex) {
    // we just changed kits
    juce::File newMapFile = mapFiles[newIndex];
    readMappingFileIntoSampler(newMapFile, true);
    selectedSoundIndex.setValue(0, nullptr);
    markAndUpdate(shouldUpdateGain);
    updateThumb();
}

void DrumSamplerViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    SamplerViewModel::valueTreePropertyChanged(treeWhosePropertyHasChanged,
                                               property);
    if (treeWhosePropertyHasChanged == state) {
        if (property == IDs::selectedSoundIndex) {
            markAndUpdate(shouldUpdateGain);
            updateThumb();
        }
    }
}

void DrumSamplerViewModel::readMappingFileIntoSampler(
    const juce::File &mappingFile, bool shouldUpdateSounds) {
    drumSampleFiles.clear();
    for (int i = 0; i < samplerPlugin->getNumSounds(); i++) {
        samplerPlugin->removeSound(i);
    }

    YAML::Node rootNode =
        YAML::LoadFile(mappingFile.getFullPathName().toStdString());
    const auto kitDir =
        samplerPlugin->edit.engine.getTemporaryFileManager().getTempFile(
            ConfigurationHelpers::DRUM_KITS_DIRECTORY_NAME);
    YAML::Node mappings = rootNode["mappings"];
    assert(mappings.IsSequence());
    auto foundDirs =
        kitDir.findChildFiles(juce::File::TypesOfFileToFind::findDirectories,
                              false, mappingFile.getFileNameWithoutExtension());
    bool isUserMap = foundDirs.size() > 0;
    for (std::size_t i = 0; i < mappings.size(); i++) {
        YAML::Node mapping = mappings[i];
        int noteNumber = mapping["note_number"].as<int>();
        juce::String fileName = mapping["file_name"].as<std::string>();

        // First check if a directory with the same name as the mapping file
        // exists in the drum_kits dir
        juce::File file;
        if (isUserMap) {
            // We need to look for the sample file in a folder with the same
            // name as the map file There's surely a better way to handle this,
            // but this way is pretty easy The only downside is that it requires
            // users to name the yaml file the same as the parent folder it
            // resides in
            file =
                kitDir.getChildFile(mappingFile.getFileNameWithoutExtension())
                    .getChildFile(fileName);
        } else {
            file = kitDir.getChildFile(fileName);
        }
        drumSampleFiles.add(file);

        // check if the drum sampler has enough sounds to cover this index:
        // if it doesnt have enough sounds we need to add one
        // otherwise just change the sound media
        int index = drumSampleFiles.size() - 1;
        if (samplerPlugin->getNumSounds() <= index) {
            juce::String error = samplerPlugin->addSound(
                file.getFullPathName(), file.getFileNameWithoutExtension(), 0.0,
                0.0, 1.0);
            jassert(error.isEmpty());
        }
        samplerPlugin->setSoundMedia(index, file.getFullPathName());
        if (shouldUpdateSounds) {
            samplerPlugin->setSoundParams(index, noteNumber, noteNumber,
                                          noteNumber);
            samplerPlugin->setSoundGains(index, 1, 0);
            samplerPlugin->setSoundExcerpt(
                index, 0,
                tracktion_engine::AudioFile(samplerPlugin->engine, file)
                    .getLength());
            samplerPlugin->setSoundOpenEnded(index, true);
        }
    }
}

void DrumSamplerViewModel::updateDrumKits() {
    mapFiles.clear();
    drumKitNames.clear();

    const auto sampleDir = ConfigurationHelpers::getTempDrumKitsDirectory(
        samplerPlugin->edit.engine);
    for (juce::DirectoryEntry entry : juce::RangedDirectoryIterator(
             sampleDir, true, "*.yaml",
             juce::File::TypesOfFileToFind::findFiles)) {
        YAML::Node node =
            YAML::LoadFile(entry.getFile().getFullPathName().toStdString());

        if (!node.IsNull()) {
            drumKitNames.add(node["name"].as<std::string>());
            mapFiles.add(entry.getFile());
        } else {
            juce::Logger::writeToLog(
                "unable to read YAML file: " +
                entry.getFile().getFullPathName().toStdString());
        }
    }
}

void DrumSamplerViewModel::updateThumb() {
    auto file = drumSampleFiles[selectedSoundIndex];
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
