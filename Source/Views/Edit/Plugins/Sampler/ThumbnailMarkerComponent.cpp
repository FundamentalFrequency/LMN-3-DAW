#include "ThumbnailMarkerComponent.h"

ThumbnailMarkerComponent::ThumbnailMarkerComponent(juce::Colour c)
    : colour(c)
{

}

void ThumbnailMarkerComponent::paint(juce::Graphics &g)
{

    g.setColour(colour);
    g.fillRect(getLocalBounds());

}