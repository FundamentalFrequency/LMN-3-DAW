#include "TapeComponent.h"
TapeComponent::TapeComponent()
{

    setSize(600, 400);

}

void TapeComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("TAPE", getLocalBounds(), juce::Justification::centred, true);

}

void TapeComponent::resized()
{

}
