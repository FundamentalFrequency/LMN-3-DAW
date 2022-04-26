#include "TitledListView.h"

TitledListView::TitledListView(const juce::StringArray &listItems,
                               const juce::String &titleString,
                               ListTitle::IconType type,
                               const juce::String &iconString)
    : listView(listItems), listTitle(titleString, type, iconString)

{
    addAndMakeVisible(listTitle);
    addAndMakeVisible(listView);
}

void TitledListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TitledListView::resized() {
    int rowHeight = getHeight() / 6;
    listView.setBounds(0, rowHeight, getWidth(), getHeight() - rowHeight);
    listTitle.setBounds(0, 0, getWidth(), rowHeight);
    listView.getListBox().setRowHeight(rowHeight);
}

SimpleListView &TitledListView::getListView() { return listView; }

void TitledListView::setListItems(const juce::StringArray &listItems) {
    listView.setListItems(listItems);
}
