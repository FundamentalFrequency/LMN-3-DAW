#include "PlayheadComponent.h"

PlayheadComponent::PlayheadComponent()
{

}
void PlayheadComponent::paint(juce::Graphics& g)
{

    g.setColour(juce::Colours::white);
    g.drawRect (0, 0, getWidth(), getHeight());

}