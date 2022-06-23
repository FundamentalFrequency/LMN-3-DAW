#include "MidiClipComponent.h"

MidiClipComponent::MidiClipComponent(tracktion::Clip::Ptr c,
                                     app_services::TimelineCamera &camera)
    : ClipComponent(c, camera) {}

tracktion::MidiClip *MidiClipComponent::getMidiClip() {
    return dynamic_cast<tracktion::MidiClip *>(clip.get());
}

void MidiClipComponent::paint(juce::Graphics &g) {
    ClipComponent::paint(g);

    if (auto mc = getMidiClip()) {
        if (mc->hasValidSequence()) {
            auto &seq = mc->getSequence();

            for (auto n : seq.getNotes()) {
                auto startBeat = mc->getStartBeat().inBeats() + n->getStartBeat().inBeats() -
                                   mc->getOffsetInBeats().inBeats();
                auto endBeat = mc->getStartBeat().inBeats() + n->getEndBeat().inBeats() -
                                 mc->getOffsetInBeats().inBeats();

                auto &tempoSequence = clip->edit.tempoSequence;

                auto startTime = tempoSequence.toTime(tracktion::BeatPosition::fromBeats(startBeat));
                auto endTime = tempoSequence.toTime(tracktion::BeatPosition::fromBeats(endBeat));

                if (auto p = getParentComponent()) {
                    double noteStartX =
                        camera.timeToX(startTime.inSeconds(), p->getWidth());
                    double noteEndX = camera.timeToX(endTime.inSeconds(), p->getWidth());
                    double y = (1.0 - double(n->getNoteNumber()) / 127.0) *
                               getHeight();

                    // startX and End are relative to track component currently
                    // need to convert to this components coordinate system
                    noteStartX = noteStartX - getX();
                    noteEndX = noteEndX - getX();

                    g.setColour(appLookAndFeel.colour3.withAlpha(
                        n->getVelocity() / 127.0f));
                    g.drawLine(float(noteStartX), float(y), float(noteEndX),
                               float(y));
                }
            }
        }
    }
}
