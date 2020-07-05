#include "DrumComponent.h"
DrumComponent::DrumComponent()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

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

juce::ApplicationCommandTarget* DrumComponent::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void DrumComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void DrumComponent::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool DrumComponent::perform (const InvocationInfo &info)
{

    return true;

}