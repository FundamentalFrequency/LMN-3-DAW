namespace app_view_models {

LowPassPluginViewModel::LowPassPluginViewModel(tracktion::LowPassPlugin *p)
    : lowPassPlugin(p) {
    normRange.start = 10;
    normRange.end = 22000;
    normRange.setSkewForCentre(500);
    lowPassPlugin->state.addListener(this);
}

LowPassPluginViewModel::~LowPassPluginViewModel() {
    lowPassPlugin->state.addListener(this);
}

double LowPassPluginViewModel::getFrequency() {
    return lowPassPlugin->frequencyValue.get();
}

void LowPassPluginViewModel::setFrequency(double freq) {
    if (lowPassPlugin->frequency->getModifiers().size() == 0)
        lowPassPlugin->frequencyValue.setValue(freq, nullptr);
}

juce::Range<double> LowPassPluginViewModel::getFrequencyRange() {
    return normRange.getRange();
}

void LowPassPluginViewModel::incrementFrequency() {
    double newNormalisedValue = normRange.convertTo0to1(getFrequency()) + .02;
    if (newNormalisedValue < 1.0)
        setFrequency(normRange.snapToLegalValue(
            normRange.convertFrom0to1(newNormalisedValue)));
    else
        setFrequency(normRange.getRange().getEnd());
}

void LowPassPluginViewModel::decrementFrequency() {
    double newNormalisedValue = normRange.convertTo0to1(getFrequency()) - .02;
    if (newNormalisedValue > 0.0)
        setFrequency(normRange.snapToLegalValue(
            normRange.convertFrom0to1(newNormalisedValue)));
    else
        setFrequency(normRange.getRange().getStart());
}

void LowPassPluginViewModel::setIsLowPass(bool isLowPass) {
    if (isLowPass)
        lowPassPlugin->mode.setValue("lowpass", nullptr);
    else
        lowPassPlugin->mode.setValue("highpass", nullptr);
}

bool LowPassPluginViewModel::getIsLowPass() {
    return lowPassPlugin->isLowPass();
}

void LowPassPluginViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == lowPassPlugin->state)
        markAndUpdate(shouldUpdateParameters);
}

void LowPassPluginViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void LowPassPluginViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->parametersChanged();
}

void LowPassPluginViewModel::removeListener(Listener *l) {
    listeners.remove(l);
}

} // namespace app_view_models
