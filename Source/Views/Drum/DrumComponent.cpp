#include "DrumComponent.h"
DrumComponent::DrumComponent()
{


}

void DrumComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("DRUM", getLocalBounds(), juce::Justification::centred, true);

}

void DrumComponent::resized()
{


}
