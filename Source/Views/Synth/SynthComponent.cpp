#include "SynthComponent.h"
SynthComponent::SynthComponent()
{


}

void SynthComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("SYNTH", getLocalBounds(), juce::Justification::centred, true);

}

void SynthComponent::resized()
{

}
