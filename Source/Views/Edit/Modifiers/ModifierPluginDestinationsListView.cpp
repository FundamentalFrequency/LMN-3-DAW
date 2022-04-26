#include "ModifierPluginDestinationsListView.h"
#include "AvailablePluginParametersListView.h"
#include <app_navigation/app_navigation.h>

ModifierPluginDestinationsListView::ModifierPluginDestinationsListView(
    tracktion_engine::AudioTrack::Ptr t, juce::Identifier identifier,
    app_services::MidiCommandManager &mcm)
    : track(t), modifierIdentifier(identifier), midiCommandManager(mcm),
      viewModel(t),
      titledList(viewModel.listViewModel.getItemNames(), "Select Plugin",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf83e)) {
    viewModel.listViewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

ModifierPluginDestinationsListView::~ModifierPluginDestinationsListView() {
    midiCommandManager.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);
}

void ModifierPluginDestinationsListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ModifierPluginDestinationsListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.listViewModel.itemListState.getSelectedItemIndex());
}

void ModifierPluginDestinationsListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(
                viewModel.listViewModel.itemListState.getSelectedItemIndex() +
                1);
}

void ModifierPluginDestinationsListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(
                viewModel.listViewModel.itemListState.getSelectedItemIndex() -
                1);
}

void ModifierPluginDestinationsListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                if (auto plugin = dynamic_cast<tracktion_engine::Plugin *>(
                        viewModel.listViewModel.getSelectedItem())) {
                    stackNavigationController->push(
                        new AvailablePluginParametersListView(
                            track, plugin, modifierIdentifier,
                            midiCommandManager));
                    midiCommandManager.setFocusedComponent(
                        stackNavigationController->getTopComponent());
                }
            }
        }
    }
}

void ModifierPluginDestinationsListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
