#include "SettingsContentComponent.h"

SettingsContentComponent::SettingsContentComponent(juce::AudioDeviceManager& dm, app_services::MidiCommandManager& mcm)
    : deviceManager(dm),
      midiCommandManager(mcm),
      deviceSelectorComponent(
        deviceManager,
        0,
        256,
        0,
        256,
        true,
        false,
        true,
        false)
{

    addAndMakeVisible(deviceSelectorComponent);
    addAndMakeVisible(graphicsTitleLabel);
    addAndMakeVisible(audioTitleLabel);

    deviceManager.addChangeListener(this);
    midiCommandManager.addListener(this);


}

SettingsContentComponent::~SettingsContentComponent()
{

    deviceManager.removeChangeListener(this);
    midiCommandManager.removeListener(this);

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

void SettingsContentComponent::encoder1Increased()
{

    auto setup = deviceManager.getAudioDeviceSetup();
    int index = deviceManager.getAvailableDeviceTypes()[0]->getDeviceNames().indexOf(setup.outputDeviceName);
    if (index < deviceManager.getAvailableDeviceTypes()[0]->getDeviceNames().size() - 1)
    {

        setup.outputDeviceName = deviceManager.getAvailableDeviceTypes()[0]->getDeviceNames()[index + 1];
        deviceManager.setAudioDeviceSetup(setup, true);

    }


}
void SettingsContentComponent::encoder1Decreased()
{


    auto setup = deviceManager.getAudioDeviceSetup();
    int index = deviceManager.getAvailableDeviceTypes()[0]->getDeviceNames().indexOf(setup.outputDeviceName);
    if (index > 0)
    {

        setup.outputDeviceName = deviceManager.getAvailableDeviceTypes()[0]->getDeviceNames()[index - 1];
        deviceManager.setAudioDeviceSetup(setup, true);
    }


}

