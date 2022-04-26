#include "SimpleListView.h"

SimpleListView::SimpleListView(const juce::StringArray &listItems)
    : listModel(std::make_unique<SimpleListModel>(listItems)) {
    listBox.setModel(listModel.get());
    listBox.updateContent();

    addAndMakeVisible(listBox);
}

void SimpleListView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void SimpleListView::resized() {
    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight(getParentHeight() / 6);
}

juce::ListBox &SimpleListView::getListBox() { return listBox; }
void SimpleListView::setListItems(const juce::StringArray &listItems) {
    listModel->setItems(listItems);
    listBox.updateContent();
}
