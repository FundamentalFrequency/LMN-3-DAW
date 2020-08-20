#include "TrackPluginsListView.h"
#include "PluginView.h"
#include <app_navigation/app_navigation.h>
#include "AvailablePluginsListView.h"

TrackPluginsListView::TrackPluginsListView(tracktion_engine::AudioTrack& t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
        : track(t),
          midiCommandManager(mcm),
          selectionManager(sm),
          viewModel(t, selectionManager),
          listView(viewModel.getPluginNames())
{

    viewModel.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

}

TrackPluginsListView::~TrackPluginsListView()
{

    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);

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
    {

        viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() + 1);

    }

}

void TrackPluginsListView::encoder1Decreased()
{

    if (isShowing())
    {

        viewModel.setSelectedPluginIndex(viewModel.getSelectedPluginIndex() - 1);

    }

}

void TrackPluginsListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        {

            if (auto plugin = viewModel.getSelectedPlugin())
            {

                // this creates the plugin "window" component (not really a window, just a component) in the window state object
                plugin->showWindowExplicitly();
                stackNavigationController->push(new PluginView(midiCommandManager, plugin, plugin->windowState->pluginWindow.get()));

            }

        }

    }

}

void TrackPluginsListView::encoder4ButtonReleased()
{

    if (isShowing())
    {
        viewModel.deleteSelectedPlugin();
    }

}

void TrackPluginsListView::pluginsButtonReleased()
{

    if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        stackNavigationController->push(new AvailablePluginsListView(&track, midiCommandManager, selectionManager));

}

void TrackPluginsListView::selectedPluginIndexChanged(int newIndex)
{
    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackPluginsListView::pluginsChanged()
{
    listView.setListItems(viewModel.getPluginNames());
    sendLookAndFeelChange();
}

