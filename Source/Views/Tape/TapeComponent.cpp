#include "TapeComponent.h"
TapeComponent::TapeComponent()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

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

juce::ApplicationCommandTarget* TapeComponent::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TapeComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void TapeComponent::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool TapeComponent::perform (const InvocationInfo &info)
{

    return true;

}
