#include "SynthComponent.h"
SynthComponent::SynthComponent()
{
    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });

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

juce::ApplicationCommandTarget* SynthComponent::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SynthComponent::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void SynthComponent::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool SynthComponent::perform (const InvocationInfo &info)
{

    return true;

}