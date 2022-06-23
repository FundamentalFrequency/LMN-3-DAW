#include "TrackViewModel.h"

namespace app_view_models {

TrackViewModel::TrackViewModel(tracktion::AudioTrack::Ptr t,
                               app_services::TimelineCamera &cam)
    : track(t), state(track->state.getOrCreateChildWithName(
                    IDs::TRACK_VIEW_STATE, nullptr)),
      camera(cam) {
    jassert(state.hasType(IDs::TRACK_VIEW_STATE));
    track->state.addListener(this);
    track->edit.getTransport().addChangeListener(this);
}

TrackViewModel::~TrackViewModel() {
    track->state.removeListener(this);
    track->edit.getTransport().removeChangeListener(this);
}

app_services::TimelineCamera &TrackViewModel::getCamera() { return camera; }

void TrackViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateClipPositions))
        listeners.call(
            [this](Listener &l) { l.clipPositionsChanged(track->getClips()); });

    if (compareAndReset(shouldUpdateClips))
        listeners.call(
            [this](Listener &l) { l.clipsChanged(track->getClips()); });

    if (compareAndReset(shouldUpdateTransport))
        listeners.call([this](Listener &l) { l.transportChanged(); });
}

void TrackViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->clipsChanged(track->getClips());
    l->clipPositionsChanged(track->getClips());
    l->transportChanged();
}

void TrackViewModel::removeListener(Listener *l) { listeners.remove(l); }

void TrackViewModel::changeListenerCallback(juce::ChangeBroadcaster *) {
    // when the transport changes state
    markAndUpdate(shouldUpdateTransport);
}

void TrackViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (tracktion::Clip::isClipState(treeWhosePropertyHasChanged)) {
        if (property == tracktion::IDs::start ||
            property == tracktion::IDs::length) {
            markAndUpdate(shouldUpdateClipPositions);
        }
    }
}

void TrackViewModel::valueTreeChildAdded(
    juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) {
    if (tracktion::Clip::isClipState(childWhichHasBeenAdded))
        markAndUpdate(shouldUpdateClips);
}

void TrackViewModel::valueTreeChildRemoved(
    juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved,
    int indexFromWhichChildWasRemoved) {
    if (tracktion::Clip::isClipState(childWhichHasBeenRemoved))
        markAndUpdate(shouldUpdateClips);
}

void TrackViewModel::valueTreeChildOrderChanged(
    juce::ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex,
    int newIndex) {
    if (tracktion::Clip::isClipState(
            parentTreeWhoseChildrenHaveMoved.getChild(oldIndex)))
        markAndUpdate(shouldUpdateClipPositions);
    else if (tracktion::Clip::isClipState(
                 parentTreeWhoseChildrenHaveMoved.getChild(newIndex)))
        markAndUpdate(shouldUpdateClipPositions);
}

} // namespace app_view_models