#include "TracksView.h"
#include "CommandList.h"
TracksView::TracksView(juce::Array<tracktion_engine::AudioTrack*> ts, juce::ApplicationCommandManager& cm)
    : commandManager(cm),
      listModel(std::make_unique<TracksListBoxModel>(ts))

{


    listBox.setModel(listModel.get());
    listBox.selectRow(0);
    addAndMakeVisible(listBox);
    listBox.updateContent();

    // Since this is the initial view, we need it to grab keyboard focus manually
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });
    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TracksView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight (getParentHeight() / 10);

}

juce::ApplicationCommandTarget* TracksView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TracksView::getAllCommands(juce::Array<juce::CommandID>& commands)
{



}

void TracksView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{


}

bool TracksView::perform (const InvocationInfo &info)
{

    return true;

}
