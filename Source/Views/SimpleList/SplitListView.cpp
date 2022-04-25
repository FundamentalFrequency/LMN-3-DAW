#include "SplitListView.h"

SplitListView::SplitListView(const juce::StringArray &leftListItems,
                             const juce::StringArray &rightListItems)
    : leftListView(leftListItems), rightListView(rightListItems) {

    addAndMakeVisible(leftListView);
    addAndMakeVisible(rightListView);
}

void SplitListView::paint(juce::Graphics &g) {

    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void SplitListView::resized() {

    rightListView.setBounds(getLocalBounds().removeFromRight(getWidth() / 2));
    leftListView.setBounds(getLocalBounds().removeFromLeft(getWidth() / 2));
}

SimpleListView &SplitListView::getLeftListView() { return leftListView; }

SimpleListView &SplitListView::getRightListView() { return rightListView; }

void SplitListView::setLeftListItems(const juce::StringArray &listItems) {

    leftListView.setListItems(listItems);
}

void SplitListView::setRightListItems(const juce::StringArray &listItems) {

    rightListView.setListItems(listItems);
}
