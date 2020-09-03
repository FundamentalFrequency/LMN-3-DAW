#include "TrackModifiersListView.h"
#include <app_navigation/app_navigation.h>
#include "AvailableModifiersListView.h"

TrackModifiersListView::TrackModifiersListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm)
        : track(t),
          midiCommandManager(mcm),
          viewModel(t),
          listView(viewModel.listViewModel.getItemNames())
{

    viewModel.listViewModel.addListener(this);
    viewModel.listViewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){listView.getListBox().scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex());});

}

TrackModifiersListView::~TrackModifiersListView()
{

    midiCommandManager.removeListener(this);
    viewModel.listViewModel.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);

}

void TrackModifiersListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TrackModifiersListView::resized()
{

    listView.setBounds(getLocalBounds());

}

void TrackModifiersListView::encoder1Increased()
{

    if (isShowing())
        viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() + 1);

}

void TrackModifiersListView::encoder1Decreased()
{

    if (isShowing())
        viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() - 1);
}

void TrackModifiersListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
        {

            if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(viewModel.listViewModel.getSelectedItem()))
            {

                // this creates the plugin "window" component (not really a window, just a component) in the window state object
//                plugin->showWindowExplicitly();
//                stackNavigationController->push(new PluginView(midiCommandManager, plugin, plugin->windowState->pluginWindow.get()));

            }

        }

    }

}

void TrackModifiersListView::plusButtonReleased()
{

    if (isShowing())
        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            stackNavigationController->push(new AvailableModifiersListView(track, midiCommandManager));

}

void TrackModifiersListView::minusButtonReleased()
{

    if (isShowing())
        viewModel.deleteSelectedModifier();

}

void TrackModifiersListView::selectedIndexChanged(int newIndex)
{
    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackModifiersListView::itemsChanged()
{
    listView.setListItems(viewModel.listViewModel.getItemNames());
    listView.getListBox().scrollToEnsureRowIsOnscreen(listView.getListBox().getSelectedRow());
    sendLookAndFeelChange();
}

