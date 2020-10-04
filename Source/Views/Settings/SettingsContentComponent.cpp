#include "SettingsContentComponent.h"

SettingsContentComponent::SettingsContentComponent(juce::AudioDeviceManager& dm)
    : deviceManager(dm),
      deviceSelectorComponent(
        deviceManager,
        0,
        256,
        0,
        256,
        true,
        false,
        false,
        false)
{

    addAndMakeVisible(deviceSelectorComponent);
    addAndMakeVisible(graphicsTitleLabel);
    addAndMakeVisible(audioTitleLabel);

    deviceManager.addChangeListener(this);



}

void SettingsContentComponent::paint(juce::Graphics& g)
{

    g.fillAll (findColour(juce::ResizableWindow::backgroundColourId));

}

void SettingsContentComponent::resized()
{

    auto bounds = getLocalBounds();
    auto space = itemHeight / 4;
    graphicsTitleLabel.setBounds(bounds.removeFromTop(itemHeight));
    bounds.removeFromTop(space);

    audioTitleLabel.setBounds(bounds.removeFromTop (itemHeight));
    bounds.removeFromTop (space);
    deviceSelectorComponent.setBounds(bounds);

}

void SettingsContentComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{

    if (source == dynamic_cast<juce::ChangeBroadcaster*>(&deviceManager))
    {
        repaint();
    }

}

