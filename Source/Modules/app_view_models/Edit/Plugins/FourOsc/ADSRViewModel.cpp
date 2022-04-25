
namespace app_view_models {

ADSRViewModel::ADSRViewModel(tracktion_engine::FourOscPlugin *p) : plugin(p) {

    plugin->state.addListener(this);
}

ADSRViewModel::~ADSRViewModel() { plugin->state.removeListener(this); }

float ADSRViewModel::getAttack() const {

    return plugin->ampAttack->getCurrentNormalisedValue();
}

float ADSRViewModel::getDecay() const {

    return plugin->ampDecay->getCurrentNormalisedValue();
}

float ADSRViewModel::getSustain() const {

    return plugin->ampSustain->getCurrentNormalisedValue();
}

float ADSRViewModel::getRelease() const {

    return plugin->ampRelease->getCurrentNormalisedValue();
}

void ADSRViewModel::incrementAttack() {

    plugin->ampAttack->setNormalisedParameter(getAttack() + .01,
                                              juce::dontSendNotification);
}

void ADSRViewModel::decrementAttack() {

    plugin->ampAttack->setNormalisedParameter(getAttack() - .01,
                                              juce::dontSendNotification);
}

void ADSRViewModel::incrementDecay() {

    plugin->ampDecay->setNormalisedParameter(getDecay() + .01,
                                             juce::dontSendNotification);
}

void ADSRViewModel::decrementDecay() {

    plugin->ampDecay->setNormalisedParameter(getDecay() - .01,
                                             juce::dontSendNotification);
}

void ADSRViewModel::incrementSustain() {

    plugin->ampSustain->setNormalisedParameter(getSustain() + .01,
                                               juce::dontSendNotification);
}

void ADSRViewModel::decrementSustain() {

    plugin->ampSustain->setNormalisedParameter(getSustain() - .01,
                                               juce::dontSendNotification);
}

void ADSRViewModel::incrementRelease() {

    plugin->ampRelease->setNormalisedParameter(getRelease() + .01,
                                               juce::dontSendNotification);
}

void ADSRViewModel::decrementRelease() {

    plugin->ampRelease->setNormalisedParameter(getRelease() - .01,
                                               juce::dontSendNotification);
}

void ADSRViewModel::handleAsyncUpdate() {

    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void ADSRViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {

    // the oscillator number is appended to the normal property name
    if (treeWhosePropertyHasChanged == plugin->state)
        if (property == tracktion_engine::IDs::ampAttack ||
            property == tracktion_engine::IDs::ampDecay ||
            property == tracktion_engine::IDs::ampSustain ||
            property == tracktion_engine::IDs::ampRelease) {
            markAndUpdate(shouldUpdateParameters);
        }
}

void ADSRViewModel::addListener(Listener *l) {

    listeners.add(l);
    l->parametersChanged();
}

void ADSRViewModel::removeListener(Listener *l) { listeners.remove(l); }

} // namespace app_view_models