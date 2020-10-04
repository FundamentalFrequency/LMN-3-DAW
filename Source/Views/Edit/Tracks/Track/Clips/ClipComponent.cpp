#include "ClipComponent.h"

ClipComponent::ClipComponent(tracktion_engine::Clip::Ptr c, app_services::TimelineCamera& cam)
 : clip(c),
   camera(cam)
{


}

void ClipComponent::paint(juce::Graphics& g)
{

    g.fillAll(clip->getClipTrack()->getColour().withAlpha (0.5f));
    g.setColour(appLookAndFeel.colour3);
    g.drawRect(getLocalBounds());

}

tracktion_engine::Clip& ClipComponent::getClip()
{

    return *clip;
}