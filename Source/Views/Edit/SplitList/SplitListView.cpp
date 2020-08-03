#include "SplitListView.h"
#include "CommandList.h"
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

    commands.add(AppCommands::INCREMENT_ENCODER_1);
    commands.add(AppCommands::DECREMENT_ENCODER_1);
    commands.add(AppCommands::INCREMENT_ENCODER_2);
    commands.add(AppCommands::DECREMENT_ENCODER_2);

}

void SplitListView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

    switch(commandID)
    {
        case INCREMENT_ENCODER_1:
            result.setInfo("Increment Encoder 1", "Increment encoder 1", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, 0);
            break;

        case DECREMENT_ENCODER_1:
            result.setInfo("Decrement Encoder 1", "Decrement encoder 1", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F9Key, juce::ModifierKeys::shiftModifier);
            break;

        case INCREMENT_ENCODER_2:
            result.setInfo("Increment Encoder 2", "Increment encoder 2", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F10Key, 0);
            break;

        case DECREMENT_ENCODER_2:
            result.setInfo("Decrement Encoder 2", "Decrement encoder 2", "Encoder", 0);
            result.addDefaultKeypress(juce::KeyPress::F10Key, juce::ModifierKeys::shiftModifier);
            break;

        default:
            break;
    }


}

bool SplitListView::perform (const InvocationInfo &info)
{

    switch(info.commandID)
    {
        case INCREMENT_ENCODER_1:
        {
            int totalItems = (leftListModel != nullptr) ? leftListModel->getNumRows() : 0;
            leftListBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, leftListBox.getLastRowSelected() + 1)));
            break;

        }

        case DECREMENT_ENCODER_1:

            leftListBox.selectRow(juce::jmax(0, leftListBox.getLastRowSelected() - 1));
            break;

        case INCREMENT_ENCODER_2:
        {
            int totalItems = (rightListModel != nullptr) ? rightListModel->getNumRows() : 0;
            rightListBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, rightListBox.getLastRowSelected() + 1)));
            break;

        }

        case DECREMENT_ENCODER_2:

            rightListBox.selectRow(juce::jmax(0, rightListBox.getLastRowSelected() - 1));
            break;

        default:
            return false;
    }
    return true;

}

void SplitListView::lookAndFeelChanged()
{

    leftListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(leftSelectedBackgroundColourId));
    rightListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(rightSelectedBackgroundColourId));
    leftListBox.updateContent();
    rightListBox.updateContent();


}
