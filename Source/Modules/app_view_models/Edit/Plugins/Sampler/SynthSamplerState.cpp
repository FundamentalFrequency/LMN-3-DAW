#include "SynthSamplerState.h"
namespace app_view_models {

SynthSamplerState::SynthSamplerState(juce::ValueTree parent, int size)
    : samplerState(
          parent.getOrCreateChildWithName(IDs::synthSamplerStateID, nullptr)),
      listSize(size) {
    jassert(samplerState.hasType(IDs::synthSamplerStateID));
    samplerState.addListener(this);

    curFilePath.referTo(samplerState, IDs::synthSamplerCurFileID, nullptr, "");
}

juce::File SynthSamplerState::getFile() {
    return juce::File{curFilePath.get()};
}

void SynthSamplerState::setFile(juce::File newFile) {
    juce::String newPath = newFile.getFullPathName();
    if (newPath != curFilePath.get())
        curFilePath.setValue(newPath, nullptr);
}

void SynthSamplerState::addListener(SynthStateListener *l) {
    listeners.add(l);
    l->fileChanged(getFile());
}

void SynthSamplerState::removeListener(SynthStateListener *l) {
    listeners.remove(l);
}

void SynthSamplerState::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateFile))
        listeners.call(
            [this](SynthStateListener &l) { l.fileChanged(getFile()); });
}

void SynthSamplerState::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == samplerState)
        if (property == app_view_models::IDs::synthSamplerCurFileID)
            markAndUpdate(shouldUpdateFile);
}

} // namespace app_view_models