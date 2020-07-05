#include "DrumView.h"
DrumView::DrumView()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void DrumView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("DRUM", getLocalBounds(), juce::Justification::centred, true);


}

void DrumView::resized()
{


}

juce::ApplicationCommandTarget* DrumView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void DrumView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void DrumView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool DrumView::perform (const InvocationInfo &info)
{

    return true;

}