#include "AvailablePluginParametersListView.h"
#include "ModifierView.h"
#include <app_navigation/app_navigation.h>
AvailablePluginParametersListView::AvailablePluginParametersListView(
    tracktion::AudioTrack::Ptr t, tracktion::Plugin::Ptr p,
    juce::Identifier modifier, app_services::MidiCommandManager &mcm)
    : track(t), plugin(p), modifierIdentifier(modifier),
      midiCommandManager(mcm), viewModel(track, plugin),
      titledList(viewModel.getItemNames(), "Select Parameter",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf83e)) {
    viewModel.itemListState.addListener(this);

    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

AvailablePluginParametersListView::~AvailablePluginParametersListView() {
    viewModel.itemListState.removeListener(this);
    midiCommandManager.removeListener(this);
}

void AvailablePluginParametersListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AvailablePluginParametersListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void AvailablePluginParametersListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
}

void AvailablePluginParametersListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
}
void AvailablePluginParametersListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                if (auto modifier =
                        dynamic_cast<tracktion::LFOModifier *>(
                            viewModel.addModifierToSelectedParameter(
                                modifierIdentifier))) {
                    stackNavigationController->push(
                        new ModifierView(modifier, midiCommandManager));
                    midiCommandManager.setFocusedComponent(
                        stackNavigationController->getTopComponent());
                }
            }
        }
    }
}

void AvailablePluginParametersListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}