#include "SplitListView.h"
#include "CommandList.h"
#include "PluginTreeItem.h"
SplitListView::SplitListView(tracktion_engine::AudioTrack* t, PluginTreeGroup& pluginGroup, juce::ApplicationCommandManager& cm)
        : track(t),
          commandManager(cm),
          pluginTreeGroup(pluginGroup),
          leftListModel(std::make_unique<SplitListBoxModel>(pluginGroup)),
          rightListModel(std::make_unique<SplitListBoxModel>(*dynamic_cast<PluginTreeGroup*>(pluginGroup.getSubItem(0))))
{


    // set default colors
    getLookAndFeel().setColour(leftSelectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(rightSelectedBackgroundColourId, juce::Colours::black);

    leftListBox.setModel(leftListModel.get());
    leftListBox.selectRow(0);
    leftListBox.getViewport()->setScrollBarsShown(false, false);
    addAndMakeVisible(leftListBox);

    rightListBox.setModel(rightListModel.get());
    rightListBox.selectRow(0);
    rightListBox.getViewport()->setScrollBarsShown(false, false);
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
    commands.add(AppCommands::SELECT_LIST_ITEM);

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

        case SELECT_LIST_ITEM:
            result.setInfo("Select List Item", "Selects the current list item", "Button", 0);
            result.addDefaultKeypress(juce::KeyPress::returnKey, 0);
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
            if (leftListBox.getLastRowSelected() != totalItems - 1)
            {
                leftListBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, leftListBox.getLastRowSelected() + 1)));

                // now we need to set the model of the right list box to match the newly selected row
                rightListModel.reset();
                rightListModel = std::make_unique<SplitListBoxModel>(*dynamic_cast<PluginTreeGroup*>(pluginTreeGroup.getSubItem(leftListBox.getSelectedRow())));
                rightListBox.setModel(rightListModel.get());
                rightListBox.selectRow(0);

                // since we created a new model, we need to update the look and feel colors from defaults
                sendLookAndFeelChange();
            }

            break;

        }

        case DECREMENT_ENCODER_1:

            if (leftListBox.getLastRowSelected() != 0)
            {
                leftListBox.selectRow(juce::jmax(0, leftListBox.getLastRowSelected() - 1));

                // now we need to set the model of the right list box to match the newly selected row
                rightListModel.reset();
                rightListModel = std::make_unique<SplitListBoxModel>(*dynamic_cast<PluginTreeGroup*>(pluginTreeGroup.getSubItem(leftListBox.getSelectedRow())));
                rightListBox.setModel(rightListModel.get());
                rightListBox.selectRow(0);

                // since we created a new model, we need to update the look and feel colors from defaults
                sendLookAndFeelChange();

            }

            break;

        case INCREMENT_ENCODER_2:
        {
            int totalItems = (rightListModel != nullptr) ? rightListModel->getNumRows() : 0;
            if (rightListBox.getLastRowSelected() != totalItems - 1)
            {
                rightListBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, rightListBox.getLastRowSelected() + 1)));
            }
            break;

        }

        case DECREMENT_ENCODER_2:

            if (rightListBox.getLastRowSelected() != 0)
            {
                rightListBox.selectRow(juce::jmax(0, rightListBox.getLastRowSelected() - 1));
            }

            break;

        case SELECT_LIST_ITEM:

            if (rightListBox.getSelectedRow() != -1)
            {

                int selectedRow = rightListBox.getSelectedRow();
                if (auto subTree = dynamic_cast<PluginTreeItem*>(rightListModel->getPluginTreeGroup().getSubItem(selectedRow)))
                {

                    if (auto plugin = subTree->create(track->edit))
                    {
                        bool pluginExistsInListAlready = false;
                        for (auto p : track->pluginList.getPlugins())
                        {
                            if (p->getIdentifierString() == plugin->getIdentifierString())
                            {
                                pluginExistsInListAlready = true;
                            }
                        }

                        if (!pluginExistsInListAlready)
                        {
                            // plugin->showWindowExplicitly();

                            if (subTree->description.isInstrument)
                            {
                                DBG("plugin is instrument");
                                if (track->pluginList.getPlugins().getUnchecked(0)->isSynth())
                                {
                                    DBG("removing current instrument first");
                                    track->pluginList.getPlugins().getFirst()->removeFromParent();

                                }
                                DBG("adding  instrument plugin to track: " + subTree->description.name);
                                DBG("at index 0");
                                track->pluginList.insertPlugin(plugin, 0, nullptr);
                            } else
                            {
                                DBG("adding effect plugin to track: " + subTree->description.name);
                                DBG("at index " + juce::String(track->pluginList.size()));
                                track->pluginList.insertPlugin(plugin, track->pluginList.size(), nullptr);
                            }


                        }

                    }

                }

                DBG("plugins on track: ");
                for (auto p : track->pluginList.getPlugins())
                {
                    DBG(p->getName());
                }

            }

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
