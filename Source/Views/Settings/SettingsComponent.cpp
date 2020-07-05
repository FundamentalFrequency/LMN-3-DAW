#include "SettingsComponent.h"

SettingsComponent::SettingsComponent()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

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

juce::ApplicationCommandTarget* SettingsComponent::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SettingsComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void SettingsComponent::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool SettingsComponent::perform (const InvocationInfo &info)
{

    return true;

}
