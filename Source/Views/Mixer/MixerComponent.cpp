#include "MixerComponent.h"

MixerComponent::MixerComponent()
{

    setSize(600, 400);

}

void MixerComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("MIXER", getLocalBounds(), juce::Justification::centred, true);

}

void MixerComponent::resized()
{

}
