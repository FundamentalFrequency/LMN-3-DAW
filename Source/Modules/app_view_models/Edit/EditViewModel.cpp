#include "EditViewModel.h"

namespace app_view_models {

EditViewModel::EditViewModel(tracktion_engine::Edit &e)
    : edit(e), state(edit.state.getOrCreateChildWithName(IDs::EDIT_VIEW_STATE,
                                                         nullptr)) {
    jassert(state.hasType(IDs::EDIT_VIEW_STATE));

    std::function<int(int)> octaveConstrainer = [this](int param) {
        return juce::jlimit(MIN_OCTAVE, MAX_OCTAVE, param);
    };

    currentOctave.setConstrainer(octaveConstrainer);
    currentOctave.referTo(state, IDs::currentOctave, nullptr, 0);

    state.addListener(this);
    edit.state.addListener(this);
}

EditViewModel::~EditViewModel() {
    state.removeListener(this);
    edit.state.removeListener(this);
}

void EditViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateOctave))
        listeners.call(
            [this](Listener &l) { l.octaveChange(currentOctave.get()); });

    if (compareAndReset(shouldUpdateTracks))
        listeners.call([this](Listener &l) { l.trackDeleted(); });
}

void EditViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->octaveChange(getCurrentOctave());
    l->trackDeleted();
}

void EditViewModel::removeListener(Listener *l) { listeners.remove(l); }

int EditViewModel::getCurrentOctave() const { return currentOctave.get(); }

void EditViewModel::setCurrentOctave(int octave) {
    currentOctave.setValue(octave, nullptr);
    tracktion_engine::EditFileOperations fileOperations(edit);
    fileOperations.save(true, true, false);
}

void EditViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == state) {
        if (property == IDs::currentOctave) {
            markAndUpdate(shouldUpdateOctave);
        }
    }
}

void EditViewModel::valueTreeChildRemoved(
    juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved,
    int indexFromWhichChildWasRemoved) {
    if (tracktion_engine::TrackList::isTrack(childWhichHasBeenRemoved)) {
        markAndUpdate(shouldUpdateTracks);
    }
}

} // namespace app_view_models
