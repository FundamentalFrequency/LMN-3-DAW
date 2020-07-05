#include "SettingsView.h"

SettingsView::SettingsView()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void SettingsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("SETTINGS", getLocalBounds(), juce::Justification::centred, true);

}

void SettingsView::resized()
{

}

juce::ApplicationCommandTarget* SettingsView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SettingsView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void SettingsView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool SettingsView::perform (const InvocationInfo &info)
{

    return true;

}
