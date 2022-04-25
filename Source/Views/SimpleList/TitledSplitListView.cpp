#include "TitledSplitListView.h"

TitledSplitListView::TitledSplitListView(
    const juce::StringArray &leftListItems,
    const juce::StringArray &rightListItems, const juce::String &titleString,
    ListTitle::IconType type, const juce::String &iconString)
    : splitListView(leftListItems, rightListItems),
      listTitle(titleString, type, iconString) {

    addAndMakeVisible(listTitle);
    addAndMakeVisible(splitListView);
}

void TitledSplitListView::paint(juce::Graphics &g) {

    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TitledSplitListView::resized() {

    int rowHeight = getHeight() / 6;
    splitListView.setBounds(0, rowHeight, getWidth(), getHeight() - rowHeight);
    listTitle.setBounds(0, 0, getWidth(), rowHeight);
    splitListView.getLeftListView().getListBox().setRowHeight(rowHeight);
    splitListView.getRightListView().getListBox().setRowHeight(rowHeight);
}

SplitListView &TitledSplitListView::getSplitListView() { return splitListView; }