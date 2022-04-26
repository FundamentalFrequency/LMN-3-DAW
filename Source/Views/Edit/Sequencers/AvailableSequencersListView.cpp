#include "AvailableSequencersListView.h"
#include "StepSequencerView.h"
#include <app_navigation/app_navigation.h>

AvailableSequencersListView::AvailableSequencersListView(
    tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager &mcm)
    : track(t), midiCommandManager(mcm), viewModel(t),
      titledList(viewModel.getItemNames(), "Sequencers",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf00a)) {
    viewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);
}

AvailableSequencersListView::~AvailableSequencersListView() {
    midiCommandManager.removeListener(this);
    viewModel.itemListState.removeListener(this);
}

void AvailableSequencersListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AvailableSequencersListView::resized() {
    titledList.setBounds(getLocalBounds());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.itemListState.getSelectedItemIndex());
}

void AvailableSequencersListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() + 1);
}

void AvailableSequencersListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(
                viewModel.itemListState.getSelectedItemIndex() - 1);
}

void AvailableSequencersListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                stackNavigationController->push(
                    new StepSequencerView(track, midiCommandManager));
                midiCommandManager.setFocusedComponent(
                    stackNavigationController->getTopComponent());
            }
        }
    }
}

void AvailableSequencersListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}
