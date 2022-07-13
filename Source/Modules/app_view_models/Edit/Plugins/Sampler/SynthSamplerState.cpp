#include "SynthSamplerState.h"
namespace app_view_models {

SynthSamplerState::SynthSamplerState(juce::ValueTree parent, int size)
    : synthSamplerValue(
          parent.getOrCreateChildWithName(IDs::synthSamplerStateID, nullptr)),
      listSize(size) {
    jassert(synthSamplerValue.hasType(IDs::synthSamplerStateID));
    synthSamplerValue.addListener(this);

    std::function<juce::String(juce::String)> noneConstrainer =
        [this](juce::String param) { return param; };

    curFilePath.setConstrainer(noneConstrainer);
    curFilePath.referTo(synthSamplerValue, IDs::synthSamplerCurFileID, nullptr,
                        "");
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
    if (treeWhosePropertyHasChanged == synthSamplerValue)
        if (property == app_view_models::IDs::synthSamplerCurFileID)
            markAndUpdate(shouldUpdateFile);
}

} // namespace app_view_models