#include "DeviceTypeListView.h"
#include <app_navigation/app_navigation.h>

DeviceTypeListView::DeviceTypeListView(tracktion_engine::Edit &e,
                                       juce::AudioDeviceManager &dm,
                                       app_services::MidiCommandManager &mcm)
    : deviceManager(dm), midiCommandManager(mcm), viewModel(e, deviceManager),
      titledList(viewModel.getItemNames(), "Device Types",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf7d9)) {

    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

DeviceTypeListView::~DeviceTypeListView() {
    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);
}

void DeviceTypeListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void DeviceTypeListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void DeviceTypeListView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
        }
    }
}

void DeviceTypeListView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
        }
    }
}

void DeviceTypeListView::encoder1ButtonReleased() {
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

void DeviceTypeListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
