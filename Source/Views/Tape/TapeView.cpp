#include "TapeView.h"
TapeView::TapeView()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void TapeView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("TAPE", getLocalBounds(), juce::Justification::centred, true);

}

void TapeView::resized()
{

}

juce::ApplicationCommandTarget* TapeView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TapeView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void TapeView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool TapeView::perform (const InvocationInfo &info)
{

    return true;

}
