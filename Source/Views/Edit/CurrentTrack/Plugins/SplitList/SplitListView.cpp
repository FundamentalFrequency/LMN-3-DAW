#include "SplitListView.h"
#include "PluginTreeItem.h"
#include <app_navigation/app_navigation.h>

SplitListView::SplitListView(tracktion_engine::AudioTrack* t, PluginTreeGroup& pluginGroup, app_services::MidiCommandManager& mcm)
        : track(t),
          midiCommandManager(mcm),
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

    midiCommandManager.addListener(this);

}

SplitListView::~SplitListView()
{

    midiCommandManager.removeListener(this);

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

void SplitListView::lookAndFeelChanged()
{

    leftListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(leftSelectedBackgroundColourId));
    rightListModel->setSelectedBackgroundColour(getLookAndFeel().findColour(rightSelectedBackgroundColourId));
    leftListBox.updateContent();
    rightListBox.updateContent();

}

void SplitListView::encoder1Increased()
{

    if (isShowing())
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

    }

}

void SplitListView::encoder1Decreased()
{

    if (isShowing())
    {

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

    }

}

void SplitListView::encoder2Increased()
{

    if (isShowing())
    {

        int totalItems = (rightListModel != nullptr) ? rightListModel->getNumRows() : 0;
        if (rightListBox.getLastRowSelected() != totalItems - 1)
        {
            rightListBox.selectRow(juce::jmin(totalItems - 1, juce::jmax(0, rightListBox.getLastRowSelected() + 1)));
        }

    }

}

void SplitListView::encoder2Decreased()
{

    if (isShowing())
    {

        if (rightListBox.getLastRowSelected() != 0)
        {
            rightListBox.selectRow(juce::jmax(0, rightListBox.getLastRowSelected() - 1));
        }

    }

}

void SplitListView::encoder2ButtonReleased()
{

    if (isShowing())
    {
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

                        if (subTree->description.isInstrument)
                        {

                            if (track->pluginList.getPlugins().getUnchecked(0)->isSynth())
                            {

                                track->pluginList.getPlugins().getFirst()->removeFromParent();

                            }

                            track->pluginList.insertPlugin(plugin, 0, nullptr);
                        } else
                        {
                            track->pluginList.insertPlugin(plugin, track->pluginList.size(), nullptr);
                        }


                    }

                }

            }

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {
                stackNavigationController->pop();
            }

        }

    }

}
