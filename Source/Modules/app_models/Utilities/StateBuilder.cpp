namespace app_models {
juce::ValueTree StateBuilder::createInitialStateTree() {
    juce::ValueTree state(IDs::APP_STATE);
    return state;
}
} // namespace app_models
