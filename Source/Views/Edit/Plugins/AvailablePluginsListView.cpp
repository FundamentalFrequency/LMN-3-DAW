#include "AvailablePluginsListView.h"
#include <app_navigation/app_navigation.h>
AvailablePluginsListView::AvailablePluginsListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm)
    : track(t),
      viewModel(t),
      midiCommandManager(mcm),
      titledSplitList(viewModel.getCategoryNames(), viewModel.getPluginNames(), "Select Plugin", ListTitle::IconType::FONT_AWESOME, juce::String::charToString(0xf1e6))
{

    viewModel.addListener(this);
    titledSplitList.getSplitListView().getRightListView().setLookAndFeel(&listItemColour2LookAndFeel);
    addAndMakeVisible(titledSplitList);
    midiCommandManager.addListener(this);


    titledSplitList.getSplitListView().getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){titledSplitList.getSplitListView().getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());});
}

AvailablePluginsListView::~AvailablePluginsListView()
{

    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);
    titledSplitList.getSplitListView().getRightListView().setLookAndFeel(nullptr);

}

void AvailablePluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AvailablePluginsListView::resized()
{

    titledSplitList.setBounds(getLocalBounds());

}

void AvailablePluginsListView::selectedCategoryIndexChanged(int newIndex)
{

    titledSplitList.getSplitListView().getLeftListView().getListBox().selectRow(newIndex);
    titledSplitList.getSplitListView().setRightListItems(viewModel.getPluginNames());
    titledSplitList.getSplitListView().getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
    sendLookAndFeelChange();

}

void AvailablePluginsListView::selectedPluginIndexChanged(int newIndex)
{

    titledSplitList.getSplitListView().getRightListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();

}

void AvailablePluginsListView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedCategoryIndex(viewModel.getSelectedCategoryIndex() + 1);

}

void AvailablePluginsListView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedCategoryIndex(viewModel.getSelectedCategoryIndex() - 1);

}

void AvailablePluginsListView::encoder2Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() + 1);

}

void AvailablePluginsListView::encoder2Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() - 1);

}

void AvailablePluginsListView::encoder2ButtonReleased()
{

    if (isShowing())
    {

        if (midiCommandManager.getFocusedComponent() == this)
        {

            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                viewModel.addSelectedPluginToTrack();
                stackNavigationController->pop();
                midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

            }

        }

    }

}

