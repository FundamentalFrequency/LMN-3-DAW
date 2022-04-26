#include "EditItemListViewModel.h"

namespace app_view_models {

EditItemListViewModel::EditItemListViewModel(
    juce::ValueTree stateToListenTo, juce::ValueTree parent,
    juce::Array<juce::Identifier> identifiersOfInterest, EditItemListAdapter *a)
    : stateToListenToForChildChanges(stateToListenTo),
      childIdentifiersOfInterest(identifiersOfInterest), adapter(a),
      itemListState(parent, adapter->size()) {
    stateToListenToForChildChanges.addListener(this);
}
EditItemListViewModel::~EditItemListViewModel() {
    stateToListenToForChildChanges.removeListener(this);
}

EditItemListAdapter *EditItemListViewModel::getAdapter() { return adapter; }

juce::StringArray EditItemListViewModel::getItemNames() {
    return adapter->getItemNames();
}

tracktion_engine::EditItem *EditItemListViewModel::getSelectedItem() {
    return adapter->getItemAtIndex(itemListState.getSelectedItemIndex());
}

void EditItemListViewModel::addListener(Listener *l) {
    listeners.add(l);
    l->itemsChanged();
}

void EditItemListViewModel::removeListener(Listener *l) { listeners.remove(l); }

void EditItemListViewModel::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateItems)) {
        // Since the number of items changed we need to update the size of the
        // list in the state object
        itemListState.listSize = adapter->size();
        // need to ensure selected index is not beyond the current number of
        // items
        if (itemListState.getSelectedItemIndex() >= itemListState.listSize) {
            itemListState.setSelectedItemIndex(itemListState.listSize - 1);
        }

        // if a previously empty list now has items, we need to set the selected
        // index to 0
        if (itemListState.getSelectedItemIndex() <= -1 &&
            itemListState.listSize > 0) {
            itemListState.setSelectedItemIndex(0);
        }

        listeners.call([this](Listener &l) { l.itemsChanged(); });
    }
}

void EditItemListViewModel::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (childIdentifiersOfInterest.contains(
            treeWhosePropertyHasChanged.getType()))
        markAndUpdate(shouldUpdateItems);
}
void EditItemListViewModel::valueTreeChildAdded(
    juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) {
    if (parentTree == stateToListenToForChildChanges) {
        if (childIdentifiersOfInterest.contains(
                childWhichHasBeenAdded.getType())) {
            markAndUpdate(shouldUpdateItems);
        }
    }
}

void EditItemListViewModel::valueTreeChildRemoved(
    juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved,
    int indexFromWhichChildWasRemoved) {
    if (parentTree == stateToListenToForChildChanges)
        if (childIdentifiersOfInterest.contains(
                childWhichHasBeenRemoved.getType()))
            markAndUpdate(shouldUpdateItems);
}

} // namespace app_view_models
