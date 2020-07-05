#include "MixerView.h"

MixerView::MixerView()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void MixerView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("MIXER", getLocalBounds(), juce::Justification::centred, true);

}

void MixerView::resized()
{

}

juce::ApplicationCommandTarget* MixerView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void MixerView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void MixerView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool MixerView::perform (const InvocationInfo &info)
{

    return true;

}
