#include "MidiClipComponent.h"

MidiClipComponent::MidiClipComponent(tracktion_engine::Clip::Ptr c, app_services::TimelineCamera& camera)
    : ClipComponent(c, camera)
{

}

tracktion_engine::MidiClip* MidiClipComponent::getMidiClip()
{

    return dynamic_cast<tracktion_engine::MidiClip*>(clip.get());

}

void MidiClipComponent::paint(juce::Graphics& g)
{

    ClipComponent::paint(g);

    if (auto mc = getMidiClip())
    {
        auto& seq = mc->getSequence();
        for (auto n : seq.getNotes())
        {
            double startBeat = mc->getStartBeat() + n->getStartBeat();
            double endBeat = mc->getStartBeat() + n->getEndBeat();

            auto& tempoSequence = clip->edit.tempoSequence;

            auto startTime = tempoSequence.beatsToTime(startBeat);
            auto endTime = tempoSequence.beatsToTime(endBeat);

            if (auto p = getParentComponent())
            {

                double noteStartX = camera.timeToX(startTime, p);
                double noteEndX = camera.timeToX(endTime, p);
                double y = (1.0 - double (n->getNoteNumber()) / 127.0) * getHeight();

                // startX and End are relative to track component currently
                // need to convert to this components coordinate system
                noteStartX = noteStartX - getX();
                noteEndX = noteEndX - getX();

                g.setColour (juce::Colours::white.withAlpha (n->getVelocity() / 127.0f));
                g.drawLine(float(noteStartX), float(y), float(noteEndX), float(y));


            }
        }
    }

}
