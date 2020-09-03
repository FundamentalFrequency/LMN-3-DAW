#include "ModifierPluginDestinationsListView.h"
#include <app_navigation/app_navigation.h>
#include "AvailablePluginParametersListView.h"

ModifierPluginDestinationsListView::ModifierPluginDestinationsListView(tracktion_engine::AudioTrack::Ptr t,
                                                                       juce::Identifier identifier,
                                                                       app_services::MidiCommandManager& mcm)
    : track(t),
      modifierIdentifier(identifier),
      midiCommandManager(mcm),
      viewModel(t),
      listView(viewModel.listViewModel.getItemNames())
{

    viewModel.listViewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(listView);

    // force list to scroll to selected index
    // for some reason had to use this timer to get it to work for rows far down in the list
    juce::Timer::callAfterDelay(1, [this](){listView.getListBox().scrollToEnsureRowIsOnscreen(viewModel.listViewModel.itemListState.getSelectedItemIndex());});

}

ModifierPluginDestinationsListView::~ModifierPluginDestinationsListView()
{

    midiCommandManager.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);

}

void ModifierPluginDestinationsListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void ModifierPluginDestinationsListView::resized()
{

    listView.setBounds(getLocalBounds());

}

void ModifierPluginDestinationsListView::encoder1Increased()
{

    if (isShowing())
        viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() + 1);

}

void ModifierPluginDestinationsListView::encoder1Decreased()
{

    if (isShowing())
        viewModel.listViewModel.itemListState.setSelectedItemIndex(viewModel.listViewModel.itemListState.getSelectedItemIndex() - 1);

}

void ModifierPluginDestinationsListView::encoder1ButtonReleased()
{

    if (isShowing())
        if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            if (auto plugin = dynamic_cast<tracktion_engine::Plugin*>(viewModel.listViewModel.getSelectedItem()))
                stackNavigationController->push(new AvailablePluginParametersListView(track, plugin, modifierIdentifier, midiCommandManager));


}

void ModifierPluginDestinationsListView::selectedIndexChanged(int newIndex)
{

    listView.getListBox().selectRow(newIndex);
    sendLookAndFeelChange();

}

