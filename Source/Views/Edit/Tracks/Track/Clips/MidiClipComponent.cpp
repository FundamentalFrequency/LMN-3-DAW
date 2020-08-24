#include "MidiClipComponent.h"

MidiClipComponent::MidiClipComponent(tracktion_engine::Clip::Ptr c)
    : ClipComponent(c)
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

                // width of track view is 7 seconds
                double viewStartTime = 0;
                double viewEndTime = 7;
                int width = p->getWidth() - getX();

                double t1 = juce::roundToInt((startTime - viewStartTime) * width / (viewEndTime - viewStartTime));
                double t2 = juce::roundToInt((endTime - viewStartTime) * width / (viewEndTime - viewStartTime));

                double y = (1.0 - double (n->getNoteNumber()) / 127.0) * getHeight();

                g.setColour (juce::Colours::white.withAlpha (n->getVelocity() / 127.0f));
                g.drawLine (float (t1), float (y), float (t2), float (y));

            }
        }
    }

}
