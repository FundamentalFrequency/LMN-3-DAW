#include "SimpleListModel.h"
#include "SimpleListItemView.h"

SimpleListModel::SimpleListModel(juce::StringArray listItems)
    : items(listItems) {}

int SimpleListModel::getNumRows() { return items.size(); }
void SimpleListModel::paintListBoxItem(int rowNumber, juce::Graphics &g,
                                       int width, int height,
                                       bool rowIsSelected) {}

juce::Component *SimpleListModel::refreshComponentForRow(
    int rowNumber, bool isRowSelected,
    juce::Component *existingComponentToUpdate) {
    auto *row = dynamic_cast<SimpleListItemView *>(existingComponentToUpdate);

    if (rowNumber < items.size()) {
        if (!row) {
            row = new SimpleListItemView(items[rowNumber]);
        }

        /* Update all properties of your custom component with the data for the
         * current row  */
        row->setTitle(items[rowNumber]);
        row->setSelected(isRowSelected);

    } else {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;
    }

    return row;
}

void SimpleListModel::setItems(juce::StringArray listItems) {
    items = listItems;
}
