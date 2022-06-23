namespace app_view_models {

InternalPluginViewModel::InternalPluginViewModel(tracktion::Plugin *p)
    : plugin(p) {
    plugin->state.addListener(this);
}

InternalPluginViewModel::~InternalPluginViewModel() {
    plugin->state.removeListener(this);
}
void InternalPluginViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void InternalPluginViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == plugin->state)
        markAndUpdate(shouldUpdateParameters);
}

void InternalPluginViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->parametersChanged();
}

void InternalPluginViewModel::removeListener(Listener *l) {
    listeners.remove(l);
}
} // namespace app_view_models