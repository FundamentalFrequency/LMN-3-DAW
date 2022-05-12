#include "MidiInputListView.h"
#include <app_navigation/app_navigation.h>

MidiInputListView::MidiInputListView(tracktion_engine::Edit &e,
                                     juce::AudioDeviceManager &dm,
                                     app_services::MidiCommandManager &mcm)
    : deviceManager(dm), midiCommandManager(mcm), viewModel(e, deviceManager),
      titledList(viewModel.getItemNames(), "Midi Input",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf58f)) {
    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

MidiInputListView::~MidiInputListView() {
    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);
}

void MidiInputListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MidiInputListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void MidiInputListView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
        }
    }
}

void MidiInputListView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
        }
    }
}

void MidiInputListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                stackNavigationController->popToRoot();
                midiCommandManager.setFocusedComponent(
                    stackNavigationController->getTopComponent());
            }
        }
    }
}

void MidiInputListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
