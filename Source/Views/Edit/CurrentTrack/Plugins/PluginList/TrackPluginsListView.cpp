#include "TrackPluginsListView.h"
#include "PluginView.h"
#include <app_navigation/app_navigation.h>
#include "AvailablePluginsListView.h"

TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
        : track(t),
          midiCommandManager(mcm),
          selectionManager(sm),
          viewModel(t, selectionManager),
          listView(viewModel.listViewModel.getItemNames())
{

    viewModel.listViewModel.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){listView.getListBox().scrollToEnsureRowIsOnscreen(viewModel.listViewModel.getSelectedItemIndex());});

}

TrackPluginsListView::~TrackPluginsListView()
{

    midiCommandManager.removeListener(this);
    viewModel.listViewModel.removeListener(this);

}

void TrackPluginsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TrackPluginsListView::resized()
{

    listView.setBounds(getLocalBounds());

}

void TrackPluginsListView::encoder1Increased()
{

    if (isShowing())
        viewModel.listViewModel.setSelectedItemIndex(viewModel.listViewModel.getSelectedItemIndex() + 1);

}

void TrackPluginsListView::encoder1Decreased()
{

    if (isShowing())
        viewModel.listViewModel.setSelectedItemIndex(viewModel.listViewModel.getSelectedItemIndex() - 1);
}

void TrackPluginsListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        {

            if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(viewModel.listViewModel.getSelectedItem()))
            {

                // this creates the plugin "window" component (not really a window, just a component) in the window state object
                plugin->showWindowExplicitly();
                stackNavigationController->push(new PluginView(midiCommandManager, plugin, plugin->windowState->pluginWindow.get()));

            }

        }

    }

}

void TrackPluginsListView::plusButtonReleased()
{

    if (isShowing())
        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            stackNavigationController->push(new AvailablePluginsListView(track, midiCommandManager, selectionManager));

}

void TrackPluginsListView::minusButtonReleased()
{

    if (isShowing())
        viewModel.deleteSelectedPlugin();

}

void TrackPluginsListView::selectedIndexChanged(int newIndex)
{
    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackPluginsListView::itemsChanged()
{
    listView.setListItems(viewModel.listViewModel.getItemNames());
    listView.getListBox().scrollToEnsureRowIsOnscreen(listView.getListBox().getSelectedRow());
    sendLookAndFeelChange();
}

