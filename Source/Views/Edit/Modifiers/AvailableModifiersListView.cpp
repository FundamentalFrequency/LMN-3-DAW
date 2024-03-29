#include "AvailableModifiersListView.h"
#include "ModifierPluginDestinationsListView.h"
#include <app_navigation/app_navigation.h>

AvailableModifiersListView::AvailableModifiersListView(
    tracktion::AudioTrack::Ptr t, app_services::MidiCommandManager &mcm)
    : track(t), midiCommandManager(mcm), viewModel(t),
      titledList(viewModel.getItemNames(), "Select Modifier",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf83e)) {
    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

AvailableModifiersListView::~AvailableModifiersListView() {
    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);
}

void AvailableModifiersListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AvailableModifiersListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void AvailableModifiersListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
}

void AvailableModifiersListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
}

void AvailableModifiersListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            auto selectedID = viewModel.getSelectedItem().identifier;
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                stackNavigationController->push(
                    new ModifierPluginDestinationsListView(track, selectedID,
                                                           midiCommandManager));
                midiCommandManager.setFocusedComponent(
                    stackNavigationController->getTopComponent());
            }
        }
    }
}

void AvailableModifiersListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
