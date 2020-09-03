#include "AvailablePluginsListView.h"
#include <app_navigation/app_navigation.h>

AvailablePluginsListView::AvailablePluginsListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm)
    : track(t),
      viewModel(t),
      midiCommandManager(mcm),
      splitListView(viewModel.getCategoryNames(), viewModel.getPluginNames())
{

    viewModel.addListener(this);
    splitListView.getRightListView().setLookAndFeel(&listItemColour2LookAndFeel);
    addAndMakeVisible(splitListView);
    midiCommandManager.addListener(this);


    splitListView.getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){splitListView.getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());});
}

AvailablePluginsListView::~AvailablePluginsListView()
{

    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);
    splitListView.getRightListView().setLookAndFeel(nullptr);

}

void AvailablePluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AvailablePluginsListView::resized()
{

    splitListView.setBounds(getLocalBounds());

}

void AvailablePluginsListView::selectedCategoryIndexChanged(int newIndex)
{

    splitListView.getLeftListView().getListBox().selectRow(newIndex);
    splitListView.setRightListItems(viewModel.getPluginNames());
    splitListView.getRightListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.getSelectedPluginIndex());
    sendLookAndFeelChange();

}

void AvailablePluginsListView::selectedPluginIndexChanged(int newIndex)
{

    splitListView.getRightListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();

}

void AvailablePluginsListView::encoder1Increased()
{

    if (isShowing())
        viewModel.setSelectedCategoryIndex(viewModel.getSelectedCategoryIndex() + 1);

}

void AvailablePluginsListView::encoder1Decreased()
{

    if (isShowing())
        viewModel.setSelectedCategoryIndex(viewModel.getSelectedCategoryIndex() - 1);

}

void AvailablePluginsListView::encoder2Increased()
{

    if (isShowing())
        viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() + 1);

}

void AvailablePluginsListView::encoder2Decreased()
{

    if (isShowing())

        viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() - 1);

}

void AvailablePluginsListView::encoder2ButtonReleased()
{

    if (isShowing())
    {

        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        {

            viewModel.addSelectedPluginToTrack();
            stackNavigationController->pop();

        }

    }

}
