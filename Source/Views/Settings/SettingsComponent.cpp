#include "SettingsComponent.h"

SettingsComponent::SettingsComponent()
{


}

void SettingsComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("SETTINGS", getLocalBounds(), juce::Justification::centred, true);

}

void SettingsComponent::resized()
{

}
