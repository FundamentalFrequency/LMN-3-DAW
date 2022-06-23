namespace app_models {

StepChannelList::StepChannelList(const juce::ValueTree &v)
    : tracktion::ValueTreeObjectList<StepChannel>(v) {
    rebuildObjects();
}

StepChannelList::~StepChannelList() { freeObjects(); }

bool StepChannelList::isSuitableType(const juce::ValueTree &v) const {
    return v.hasType(IDs::STEP_CHANNEL);
}

StepChannel *StepChannelList::createNewObject(const juce::ValueTree &v) {
    return new StepChannel(v);
}

void StepChannelList::deleteObject(StepChannel *sc) { delete sc; }

void StepChannelList::newObjectAdded(StepChannel *sc) {}

void StepChannelList::objectRemoved(StepChannel *sc) {}

void StepChannelList::objectOrderChanged() {}
} // namespace app_models