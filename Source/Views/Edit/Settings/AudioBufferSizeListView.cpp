#include "AudioBufferSizeListView.h"
#include <app_navigation/app_navigation.h>

AudioBufferSizeListView::AudioBufferSizeListView(
    tracktion::Edit &e, juce::AudioDeviceManager &dm,
    app_services::MidiCommandManager &mcm)
    : deviceManager(dm), midiCommandManager(mcm), viewModel(e, deviceManager),
      titledList(viewModel.getItemNames(), "Audio Buffer Size",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf2f2)) {
    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

AudioBufferSizeListView::~AudioBufferSizeListView() {
    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);
}

void AudioBufferSizeListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioBufferSizeListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void AudioBufferSizeListView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
        }
    }
}

void AudioBufferSizeListView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
        }
    }
}

void AudioBufferSizeListView::encoder1ButtonReleased() {
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

void AudioBufferSizeListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
