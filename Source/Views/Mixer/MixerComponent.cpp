#include "MixerComponent.h"

MixerComponent::MixerComponent()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

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

juce::ApplicationCommandTarget* MixerComponent::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void MixerComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void MixerComponent::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool MixerComponent::perform (const InvocationInfo &info)
{

    return true;

}
