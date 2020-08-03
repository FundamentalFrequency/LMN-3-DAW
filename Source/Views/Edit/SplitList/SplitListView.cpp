#include "SplitListView.h"
#include <juce_audio_processors/juce_audio_processors.h>
SplitListView::SplitListView(PluginTreeGroup& pluginGroup, juce::ApplicationCommandManager& cm)
        : commandManager(cm),
          leftListModel(std::make_unique<ListBoxModel>(pluginGroup)),
          rightListModel(std::make_unique<ListBoxModel>(*dynamic_cast<PluginTreeGroup*>(pluginGroup.getSubItem(0))))
{

    // set default colors
    getLookAndFeel().setColour(leftSelectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(rightSelectedBackgroundColourId, juce::Colours::black);

    leftListBox.setModel(leftListModel.get());
    leftListBox.selectRow(0);
    addAndMakeVisible(leftListBox);

    rightListBox.setModel(rightListModel.get());
    rightListBox.selectRow(0);
    addAndMakeVisible(rightListBox);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void SplitListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void SplitListView::resized()
{

    rightListBox.setBounds(getLocalBounds().removeFromRight(getWidth() / 2));
    leftListBox.setBounds(getLocalBounds().removeFromLeft(getWidth() / 2));
    leftListBox.setRowHeight(getParentHeight() / 10);
    rightListBox.setRowHeight(getParentHeight() / 10);

}

juce::ApplicationCommandTarget* SplitListView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void SplitListView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void SplitListView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool SplitListView::perform (const InvocationInfo &info)
{

    return true;

}

void SplitListView::lookAndFeelChanged()
{

    leftListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(leftSelectedBackgroundColourId));
    rightListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(rightSelectedBackgroundColourId));
    leftListBox.updateContent();
    rightListBox.updateContent();
}
