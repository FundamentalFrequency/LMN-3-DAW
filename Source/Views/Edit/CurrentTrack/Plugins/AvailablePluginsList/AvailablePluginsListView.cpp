#include "AvailablePluginsListView.h"
#include <app_navigation/app_navigation.h>

AvailablePluginsListView::AvailablePluginsListView(tracktion_engine::AudioTrack* t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
    : track(t),
      viewModel(*t, sm),
      midiCommandManager(mcm),
      splitListView(viewModel.getCategoryNames(), viewModel.getPluginNames())
{

    viewModel.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(splitListView);
}

AvailablePluginsListView::~AvailablePluginsListView()
{

    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);

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

}

void AvailablePluginsListView::selectedPluginIndexChanged(int newIndex)
{

    splitListView.getRightListView().getListBox().selectRow(newIndex);

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
