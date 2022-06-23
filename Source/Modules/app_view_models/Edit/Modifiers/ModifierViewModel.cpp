namespace app_view_models {

ModifierViewModel::ModifierViewModel(tracktion::Modifier *mod)
    : modifier(mod) {
    modifier->state.addListener(this);
}

ModifierViewModel::~ModifierViewModel() {
    modifier->state.removeListener(this);
}
void ModifierViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateParameters))
        listeners.call([this](Listener &l) { l.parametersChanged(); });
}

void ModifierViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == modifier->state)
        markAndUpdate(shouldUpdateParameters);
}

void ModifierViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->parametersChanged();
}

void ModifierViewModel::removeListener(Listener *l) { listeners.remove(l); }
} // namespace app_view_models