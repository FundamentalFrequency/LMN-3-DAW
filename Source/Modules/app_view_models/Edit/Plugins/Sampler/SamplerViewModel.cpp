
namespace app_view_models {

SamplerViewModel::SamplerViewModel(tracktion::SamplerPlugin *sampler,
                                   juce::Identifier stateIdentifier)
    : samplerPlugin(sampler),
      state(samplerPlugin->edit.state.getOrCreateChildWithName(stateIdentifier,
                                                               nullptr)),
      itemListState(state, 100), fullSampleThumbnailCache(5),
      fullSampleThumbnail(numSamplesForThumbnail, formatManager,
                          fullSampleThumbnailCache) {
    formatManager.registerBasicFormats();
    selectedSoundIndex.referTo(state, IDs::selectedSoundIndex, nullptr, 0);
    samplerPlugin->state.addListener(this);
    fullSampleThumbnail.addChangeListener(this);
    itemListState.addListener(this);
    state.addListener(this);
}

SamplerViewModel::~SamplerViewModel() {
    samplerPlugin->state.removeListener(this);
    itemListState.removeListener(this);
    state.removeListener(this);
    fullSampleThumbnail.removeChangeListener(this);
}

juce::String SamplerViewModel::getSelectedItemName() {
    return getItemNames()[itemListState.getSelectedItemIndex()];
}

juce::AudioThumbnail &SamplerViewModel::getFullSampleThumbnail() {
    return fullSampleThumbnail;
}

double SamplerViewModel::getStartTime() {
    return samplerPlugin->getSoundStartTime(selectedSoundIndex);
}

double SamplerViewModel::getEndTime() {
    return samplerPlugin->getSoundStartTime(selectedSoundIndex) +
           samplerPlugin->getSoundLength(selectedSoundIndex);
}

double SamplerViewModel::getGain() {
    return samplerPlugin->getSoundGainDb(selectedSoundIndex);
}

void SamplerViewModel::increaseSelectedIndex() {
    itemListState.setSelectedItemIndex(itemListState.getSelectedItemIndex() +
                                       1);
}

void SamplerViewModel::decreaseSelectedIndex() {
    itemListState.setSelectedItemIndex(itemListState.getSelectedItemIndex() -
                                       1);
}

void SamplerViewModel::increaseStartTime() {
    double increment =
        samplerPlugin->getSoundFile(selectedSoundIndex).getLength() / 100.0;
    if (samplerPlugin->getSoundLength(selectedSoundIndex) >
        increment + increment / 2.0) {
        double start =
            samplerPlugin->getSoundStartTime(selectedSoundIndex) + increment;
        double length =
            samplerPlugin->getSoundLength(selectedSoundIndex) - increment;

        samplerPlugin->setSoundExcerpt(selectedSoundIndex, start, length);
    }
}

void SamplerViewModel::decreaseStartTime() {
    double decrement =
        samplerPlugin->getSoundFile(selectedSoundIndex).getLength() / 100.0;
    double start = samplerPlugin->getSoundStartTime(selectedSoundIndex);
    double length = samplerPlugin->getSoundLength(selectedSoundIndex);

    if (start > decrement) {
        start = start - decrement;
        length = length + decrement;
    } else {
        length = length + start;
        start = 0;
    }

    samplerPlugin->setSoundExcerpt(selectedSoundIndex, start, length);
}

void SamplerViewModel::increaseEndTime() {
    double increment =
        samplerPlugin->getSoundFile(selectedSoundIndex).getLength() / 100.0;
    double currentEnd = samplerPlugin->getSoundStartTime(selectedSoundIndex) +
                        samplerPlugin->getSoundLength(selectedSoundIndex);

    if (currentEnd <
        samplerPlugin->getSoundFile(selectedSoundIndex).getLength() -
            increment) {
        samplerPlugin->setSoundExcerpt(
            selectedSoundIndex,
            samplerPlugin->getSoundStartTime(selectedSoundIndex),
            samplerPlugin->getSoundLength(selectedSoundIndex) + increment);
    } else {
        samplerPlugin->setSoundExcerpt(
            selectedSoundIndex,
            samplerPlugin->getSoundStartTime(selectedSoundIndex),
            samplerPlugin->getSoundFile(selectedSoundIndex).getLength() -
                samplerPlugin->getSoundStartTime(selectedSoundIndex));
    }
}

void SamplerViewModel::decreaseEndTime() {
    double decrement =
        samplerPlugin->getSoundFile(selectedSoundIndex).getLength() / 100.0;
    double currentEnd = samplerPlugin->getSoundStartTime(selectedSoundIndex) +
                        samplerPlugin->getSoundLength(selectedSoundIndex);

    if (currentEnd > samplerPlugin->getSoundStartTime(selectedSoundIndex) +
                         decrement + decrement / 2.0) {
        samplerPlugin->setSoundExcerpt(
            selectedSoundIndex,
            samplerPlugin->getSoundStartTime(selectedSoundIndex),
            samplerPlugin->getSoundLength(selectedSoundIndex) - decrement);
    }
}

void SamplerViewModel::toggleSamplePlayDirection() {
    // Not sure if there is a way to do this
    ;
}

void SamplerViewModel::increaseGain() {
    samplerPlugin->setSoundGains(
        selectedSoundIndex,
        samplerPlugin->getSoundGainDb(selectedSoundIndex) + 1,
        samplerPlugin->getSoundPan(selectedSoundIndex));
}

void SamplerViewModel::decreaseGain() {
    samplerPlugin->setSoundGains(
        selectedSoundIndex,
        samplerPlugin->getSoundGainDb(selectedSoundIndex) - 1,
        samplerPlugin->getSoundPan(selectedSoundIndex));
}

void SamplerViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateSample))
        listeners.call([this](Listener &l) { l.sampleChanged(); });

    if (compareAndReset(shouldUpdateFullSampleThumbnail))
        listeners.call([this](Listener &l) { l.fullSampleThumbnailChanged(); });

    if (compareAndReset(shouldUpdateSampleExcerptTimes))
        listeners.call([this](Listener &l) { l.sampleExcerptTimesChanged(); });

    if (compareAndReset(shouldUpdateGain))
        listeners.call([this](Listener &l) { l.gainChanged(); });
}

void SamplerViewModel::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == &fullSampleThumbnail)
        markAndUpdate(shouldUpdateFullSampleThumbnail);
}

void SamplerViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged.hasType(tracktion::IDs::SOUND)) {
        markAndUpdate(shouldUpdateSampleExcerptTimes);

        if (property == tracktion::IDs::gainDb)
            markAndUpdate(shouldUpdateGain);
    }
}

void SamplerViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->sampleChanged();
    l->gainChanged();
}

void SamplerViewModel::removeListener(Listener *l) { listeners.remove(l); }
} // namespace app_view_models
