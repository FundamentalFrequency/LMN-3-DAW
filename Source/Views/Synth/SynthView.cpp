#include "SynthView.h"
SynthView::SynthView()
{
    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });

}

void SynthView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("SYNTH", getLocalBounds(), juce::Justification::centred, true);

}

void SynthView::resized()
{

}

juce::ApplicationCommandTarget* SynthView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SynthView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void SynthView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool SynthView::perform (const InvocationInfo &info)
{

    return true;

}