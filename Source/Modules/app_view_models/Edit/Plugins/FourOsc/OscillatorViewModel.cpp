#include "OscillatorViewModel.h"
namespace app_view_models {

OscillatorViewModel::OscillatorViewModel(tracktion::FourOscPlugin *p,
                                         int oscIndex)
    : plugin(p), oscillatorIndex(oscIndex) {
    plugin->state.addListener(this);
}

OscillatorViewModel::~OscillatorViewModel() {
    plugin->state.removeListener(this);
}

int OscillatorViewModel::getWaveShape() const {
    return plugin->oscParams[oscillatorIndex]->waveShapeValue.get();
}

int OscillatorViewModel::getVoices() const {
    return plugin->oscParams[oscillatorIndex]->voicesValue.get();
}

float OscillatorViewModel::getTune() const {
    return plugin->oscParams[oscillatorIndex]
        ->tune->getCurrentNormalisedValue();
}

float OscillatorViewModel::getFineTune() const {
    return plugin->oscParams[oscillatorIndex]
        ->fineTune->getCurrentNormalisedValue();
}

float OscillatorViewModel::getLevel() const {
    return plugin->oscParams[oscillatorIndex]
        ->level->getCurrentNormalisedValue();
}

float OscillatorViewModel::getPulseWidth() const {
    return plugin->oscParams[oscillatorIndex]
        ->pulseWidth->getCurrentNormalisedValue();
}

float OscillatorViewModel::getDetune() const {
    return plugin->oscParams[oscillatorIndex]
        ->detune->getCurrentNormalisedValue();
}

float OscillatorViewModel::getSpread() const {
    return plugin->oscParams[oscillatorIndex]
        ->spread->getCurrentNormalisedValue();
}

float OscillatorViewModel::getPan() const {
    return plugin->oscParams[oscillatorIndex]->pan->getCurrentNormalisedValue();
}

void OscillatorViewModel::incrementWaveShape() {
    if (getWaveShape() < 6)
        plugin->oscParams[oscillatorIndex]->waveShapeValue.setValue(
            getWaveShape() + 1, nullptr);
}

void OscillatorViewModel::decrementWaveShape() {
    if (getWaveShape() > 0)
        plugin->oscParams[oscillatorIndex]->waveShapeValue.setValue(
            getWaveShape() - 1, nullptr);
}

void OscillatorViewModel::incrementVoices() {
    if (getVoices() < 8)
        plugin->oscParams[oscillatorIndex]->voicesValue.setValue(
            getVoices() + 1, nullptr);
}

void OscillatorViewModel::decrementVoices() {
    if (getVoices() > 1)
        plugin->oscParams[oscillatorIndex]->voicesValue.setValue(
            getVoices() - 1, nullptr);
}

void OscillatorViewModel::incrementTune() {
    plugin->oscParams[oscillatorIndex]->tune->setNormalisedParameter(
        getTune() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementTune() {
    plugin->oscParams[oscillatorIndex]->tune->setNormalisedParameter(
        getTune() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementFineTune() {
    plugin->oscParams[oscillatorIndex]->fineTune->setNormalisedParameter(
        getFineTune() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementFineTune() {
    plugin->oscParams[oscillatorIndex]->fineTune->setNormalisedParameter(
        getFineTune() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementLevel() {
    plugin->oscParams[oscillatorIndex]->level->setNormalisedParameter(
        getLevel() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementLevel() {
    plugin->oscParams[oscillatorIndex]->level->setNormalisedParameter(
        getLevel() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementPulseWidth() {
    plugin->oscParams[oscillatorIndex]->pulseWidth->setNormalisedParameter(
        getPulseWidth() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementPulseWidth() {
    plugin->oscParams[oscillatorIndex]->pulseWidth->setNormalisedParameter(
        getPulseWidth() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementDetune() {
    plugin->oscParams[oscillatorIndex]->detune->setNormalisedParameter(
        getDetune() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementDetune() {
    plugin->oscParams[oscillatorIndex]->detune->setNormalisedParameter(
        getDetune() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementSpread() {
    plugin->oscParams[oscillatorIndex]->spread->setNormalisedParameter(
        getSpread() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementSpread() {
    plugin->oscParams[oscillatorIndex]->spread->setNormalisedParameter(
        getSpread() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::incrementPan() {
    plugin->oscParams[oscillatorIndex]->pan->setNormalisedParameter(
        getPan() + .01, juce::dontSendNotification);
}

void OscillatorViewModel::decrementPan() {
    plugin->oscParams[oscillatorIndex]->pan->setNormalisedParameter(
        getPan() - .01, juce::dontSendNotification);
}

void OscillatorViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void OscillatorViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    // the oscillator number is appended to the normal property name
    if (treeWhosePropertyHasChanged == plugin->state)
        if (property.toString().contains(tracktion::IDs::waveShape) ||
            property.toString().contains(tracktion::IDs::voices) ||
            property.toString().contains(tracktion::IDs::tune) ||
            property.toString().contains(tracktion::IDs::fineTune) ||
            property.toString().contains(tracktion::IDs::level) ||
            property.toString().contains(tracktion::IDs::pulseWidth) ||
            property.toString().contains(tracktion::IDs::detune) ||
            property.toString().contains(tracktion::IDs::spread) ||
            property.toString().contains(tracktion::IDs::pan)) {
            markAndUpdate(shouldUpdateParameters);
        }
}

void OscillatorViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->parametersChanged();
}

void OscillatorViewModel::removeListener(Listener *l) { listeners.remove(l); }

} // namespace app_view_models