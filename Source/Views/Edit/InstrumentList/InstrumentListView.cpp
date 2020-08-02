#include "InstrumentListView.h"
#include <juce_audio_processors/juce_audio_processors.h>
InstrumentListView::InstrumentListView(juce::Array<PluginListItem> listItems, juce::ApplicationCommandManager& cm)
    : commandManager(cm),
      listModel(std::make_unique<InstrumentListBoxModel>(listItems))
{

    listBox.setModel(listModel.get());
    listBox.selectRow(0);
    addAndMakeVisible(listBox);

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void InstrumentListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void InstrumentListView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight (getParentHeight() / 10);

}

juce::ApplicationCommandTarget* InstrumentListView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void InstrumentListView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void InstrumentListView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool InstrumentListView::perform (const InvocationInfo &info)
{

    return true;

}
