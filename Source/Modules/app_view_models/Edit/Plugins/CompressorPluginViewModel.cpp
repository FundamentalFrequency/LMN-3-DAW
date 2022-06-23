namespace app_view_models {

CompressorPluginViewModel::CompressorPluginViewModel(
    tracktion::CompressorPlugin *p)
    : InternalPluginViewModel(p), compressorPlugin(p) {
    compressorPlugin->useSidechainTrigger.setValue(false, nullptr);
}

int CompressorPluginViewModel::getNumberOfParameters() {
    return compressorPlugin->getNumAutomatableParameters();
}

juce::String CompressorPluginViewModel::getParameterName(int index) {
    return compressorPlugin->getAutomatableParameter(index)->getParameterName();
}

double CompressorPluginViewModel::getParameterValue(int index) {
    return compressorPlugin->getAutomatableParameter(index)
        ->getCurrentNormalisedValue();
}

void CompressorPluginViewModel::setParameterValue(int index, double value) {
    if (compressorPlugin->getAutomatableParameter(index)
            ->getModifiers()
            .size() == 0)
        compressorPlugin->getAutomatableParameter(index)
            ->setNormalisedParameter(float(value), juce::dontSendNotification);
}

} // namespace app_view_models