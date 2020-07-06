#include "SettingsView.h"

SettingsView::SettingsView(juce::AudioDeviceManager& deviceManager,juce::ValueTree v)
    : themes(v),
      settingsContentComponent(deviceManager, themes)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    settingsViewport.setViewedComponent (&settingsContentComponent, false);
    addAndMakeVisible(settingsViewport);


}

void SettingsView::paint(juce::Graphics& g)
{

}

void SettingsView::resized()
{

    auto r = getLocalBounds();
    auto scrollBarWidth = getLookAndFeel().getDefaultScrollbarWidth();
    settingsContentComponent.setSize(juce::jmax (r.getWidth() - scrollBarWidth, settingsContentComponent.getMinimumWidth()),
                          juce::jmax(r.getHeight(), settingsContentComponent.getMinimumHeight()));
    settingsViewport.setBounds(r);


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
