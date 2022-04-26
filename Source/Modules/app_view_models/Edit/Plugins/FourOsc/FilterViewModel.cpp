namespace app_view_models {

FilterViewModel::FilterViewModel(tracktion_engine::FourOscPlugin *p)
    : plugin(p) {
    plugin->state.addListener(this);
    filterNormRange.start = 8;
    filterNormRange.end = 20000;
    filterNormRange.setSkewForCentre(500);
}

FilterViewModel::~FilterViewModel() { plugin->state.removeListener(this); }

float FilterViewModel::getAttack() const {
    return plugin->filterAttack->getCurrentNormalisedValue();
}

float FilterViewModel::getDecay() const {
    return plugin->filterDecay->getCurrentNormalisedValue();
}

float FilterViewModel::getSustain() const {
    return plugin->filterSustain->getCurrentNormalisedValue();
}

float FilterViewModel::getRelease() const {
    return plugin->filterRelease->getCurrentNormalisedValue();
}

float FilterViewModel::getFrequency() const {
    return plugin->filterFreqValue.get();
}

float FilterViewModel::getResonance() const {
    return plugin->filterResonance->getCurrentNormalisedValue();
}

float FilterViewModel::getEnvelopeAmount() const {
    return plugin->filterAmount->getCurrentNormalisedValue();
}

int FilterViewModel::getFilterType() const {
    return plugin->filterTypeValue.get();
}

void FilterViewModel::incrementAttack() {
    plugin->filterAttack->setNormalisedParameter(getAttack() + .01,
                                                 juce::dontSendNotification);
}

void FilterViewModel::decrementAttack() {
    plugin->filterAttack->setNormalisedParameter(getAttack() - .01,
                                                 juce::dontSendNotification);
}

void FilterViewModel::incrementDecay() {
    plugin->filterDecay->setNormalisedParameter(getDecay() + .01,
                                                juce::dontSendNotification);
}

void FilterViewModel::decrementDecay() {
    plugin->filterDecay->setNormalisedParameter(getDecay() - .01,
                                                juce::dontSendNotification);
}

void FilterViewModel::incrementSustain() {
    plugin->filterSustain->setNormalisedParameter(getSustain() + .01,
                                                  juce::dontSendNotification);
}

void FilterViewModel::decrementSustain() {
    plugin->filterSustain->setNormalisedParameter(getSustain() - .01,
                                                  juce::dontSendNotification);
}

void FilterViewModel::incrementRelease() {
    plugin->filterRelease->setNormalisedParameter(getRelease() + .01,
                                                  juce::dontSendNotification);
}

void FilterViewModel::decrementRelease() {
    plugin->filterRelease->setNormalisedParameter(getRelease() - .01,
                                                  juce::dontSendNotification);
}

void FilterViewModel::incrementFrequency() {
    double newNormalisedValue =
        filterNormRange.convertTo0to1(plugin->filterFreqValue.get()) + .02;
    if (newNormalisedValue < 1.0)
        plugin->filterFreqValue.setValue(
            filterNormRange.snapToLegalValue(
                filterNormRange.convertFrom0to1(newNormalisedValue)),
            nullptr);
    else
        plugin->filterFreqValue.setValue(filterNormRange.getRange().getEnd(),
                                         nullptr);
}

void FilterViewModel::decrementFrequency() {
    double newNormalisedValue =
        filterNormRange.convertTo0to1(plugin->filterFreqValue.get()) - .02;
    if (newNormalisedValue > 0.0)
        plugin->filterFreqValue.setValue(
            filterNormRange.snapToLegalValue(
                filterNormRange.convertFrom0to1(newNormalisedValue)),
            nullptr);
    else
        plugin->filterFreqValue.setValue(filterNormRange.getRange().getStart(),
                                         nullptr);
}

void FilterViewModel::incrementResonance() {
    plugin->filterResonance->setNormalisedParameter(getResonance() + .01,
                                                    juce::dontSendNotification);
}

void FilterViewModel::decrementResonance() {
    plugin->filterResonance->setNormalisedParameter(getResonance() - .01,
                                                    juce::dontSendNotification);
}

void FilterViewModel::incrementEnvelopeAmount() {
    plugin->filterAmount->setNormalisedParameter(getEnvelopeAmount() + .01,
                                                 juce::dontSendNotification);
}

void FilterViewModel::decrementEnvelopeAmount() {
    plugin->filterAmount->setNormalisedParameter(getEnvelopeAmount() - .01,
                                                 juce::dontSendNotification);
}

void FilterViewModel::incrementFilterType() {
    if (getFilterType() < 4)
        plugin->filterTypeValue.setValue(getFilterType() + 1, nullptr);
}

void FilterViewModel::decrementFilterType() {
    if (getFilterType() > 0)
        plugin->filterTypeValue.setValue(getFilterType() - 1, nullptr);
}

void FilterViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void FilterViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    // the oscillator number is appended to the normal property name
    if (treeWhosePropertyHasChanged == plugin->state)
        if (property == tracktion_engine::IDs::filterAttack ||
            property == tracktion_engine::IDs::filterDecay ||
            property == tracktion_engine::IDs::filterSustain ||
            property == tracktion_engine::IDs::filterRelease ||
            property == tracktion_engine::IDs::filterFreq ||
            property == tracktion_engine::IDs::filterResonance ||
            property == tracktion_engine::IDs::filterAmount ||
            property == tracktion_engine::IDs::filterType) {
            markAndUpdate(shouldUpdateParameters);
        }
}

void FilterViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->parametersChanged();
}

void FilterViewModel::removeListener(Listener *l) { listeners.remove(l); }

} // namespace app_view_models
