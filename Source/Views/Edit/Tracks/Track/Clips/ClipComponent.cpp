#include "ClipComponent.h"

ClipComponent::ClipComponent(tracktion_engine::Clip::Ptr c)
 : clip(c)
{

}

void ClipComponent::paint(juce::Graphics& g)
{

    g.fillAll(clip->getColour().withAlpha (0.5f));
    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds());

}

tracktion_engine::Clip& ClipComponent::getClip()
{

    return *clip;
}