#include "AvailableModifiersListView.h"
#include <app_navigation/app_navigation.h>
#include "AvailableModifierPluginDestinationsListView.h"
AvailableModifiersListView::AvailableModifiersListView(tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager& mcm)
        : track(t),
          midiCommandManager(mcm),
          viewModel(t),
          listView(viewModel.getItemNames())
{

    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){listView.getListBox().scrollToEnsureRowIsOnscreen(viewModel.itemListState.getSelectedItemIndex());});

}

AvailableModifiersListView::~AvailableModifiersListView()
{

    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);

}

void AvailableModifiersListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AvailableModifiersListView::resized()
{

    listView.setBounds(getLocalBounds());

}

void AvailableModifiersListView::encoder1Increased()
{

    if (isShowing())
        viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() + 1);

}

void AvailableModifiersListView::encoder1Decreased()
{

    if (isShowing())
        viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() - 1);
}

void AvailableModifiersListView::encoder1ButtonReleased()
{

    if (isShowing())
    {

        auto selectedID = viewModel.getSelectedItem().identifier;
        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            stackNavigationController->push(new AvailableModifierPluginDestinationsListView(track, selectedID, midiCommandManager));

    }

}

void AvailableModifiersListView::selectedIndexChanged(int newIndex)
{
    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

