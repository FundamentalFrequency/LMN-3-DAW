#include "TrackModifiersListView.h"
#include "AvailableModifiersListView.h"
#include "ModifierView.h"
#include <app_navigation/app_navigation.h>
TrackModifiersListView::TrackModifiersListView(
    tracktion_engine::AudioTrack::Ptr t, app_services::MidiCommandManager &mcm)
    : track(t), midiCommandManager(mcm), viewModel(t),
      titledList(viewModel.listViewModel.getItemNames(), "Modifiers",
                 ListTitle::IconType::FONT_AWESOME,
                 juce::String::charToString(0xf83e)) {
    viewModel.listViewModel.addListener(this);
    viewModel.listViewModel.itemListState.addListener(this);
    midiCommandManager.addListener(this);

    emptyListLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1,
                   juce::Font::plain));
    emptyListLabel.setText("Press + to add a modifier!",
                           juce::dontSendNotification);
    emptyListLabel.setJustificationType(juce::Justification::centred);
    emptyListLabel.setAlwaysOnTop(true);
    emptyListLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addChildComponent(emptyListLabel);

    addAndMakeVisible(titledList);
}

TrackModifiersListView::~TrackModifiersListView() {
    midiCommandManager.removeListener(this);
    viewModel.listViewModel.removeListener(this);
    viewModel.listViewModel.itemListState.removeListener(this);
    emptyListLabel.setLookAndFeel(nullptr);
}

void TrackModifiersListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TrackModifiersListView::resized() {
    emptyListLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1,
                   juce::Font::plain));
    emptyListLabel.setBounds(getLocalBounds());

    titledList.setBounds(getLocalBounds());

    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        viewModel.listViewModel.itemListState.getSelectedItemIndex());
}

void TrackModifiersListView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(
                viewModel.listViewModel.itemListState.getSelectedItemIndex() +
                1);
}

void TrackModifiersListView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.listViewModel.itemListState.setSelectedItemIndex(
                viewModel.listViewModel.itemListState.getSelectedItemIndex() -
                1);
}

void TrackModifiersListView::encoder1ButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                if (auto modifier =
                        dynamic_cast<tracktion_engine::LFOModifier *>(
                            viewModel.listViewModel.getSelectedItem())) {
                    stackNavigationController->push(
                        new ModifierView(modifier, midiCommandManager));
                    midiCommandManager.setFocusedComponent(
                        stackNavigationController->getTopComponent());
                }
            }
        }
    }
}

void TrackModifiersListView::plusButtonReleased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (auto stackNavigationController = findParentComponentOfClass<
                    app_navigation::StackNavigationController>()) {
                stackNavigationController->push(
                    new AvailableModifiersListView(track, midiCommandManager));
                midiCommandManager.setFocusedComponent(
                    stackNavigationController->getTopComponent());
            }
        }
    }
}

void TrackModifiersListView::minusButtonReleased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            if (midiCommandManager.getFocusedComponent() == this)
                viewModel.deleteSelectedModifier();
}

void TrackModifiersListView::selectedIndexChanged(int newIndex) {
    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();
}

void TrackModifiersListView::itemsChanged() {
    if (viewModel.listViewModel.getItemNames().size() <= 0)
        emptyListLabel.setVisible(true);
    else
        emptyListLabel.setVisible(false);

    titledList.setListItems(viewModel.listViewModel.getItemNames());
    titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(
        titledList.getListView().getListBox().getSelectedRow());
    sendLookAndFeelChange();
    repaint();
}

void TrackModifiersListView::encoder4ButtonReleased() {
    viewModel.toggleSelectedModifierEnabled();
}
