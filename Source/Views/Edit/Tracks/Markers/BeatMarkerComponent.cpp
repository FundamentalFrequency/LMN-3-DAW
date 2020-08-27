#include "BeatMarkerComponent.h"

BeatMarkerComponent::BeatMarkerComponent()
{

}
void BeatMarkerComponent::paint(juce::Graphics& g)
{

    g.setColour(markerColour);
    g.drawRect (0, 0, getWidth(), getHeight());
}