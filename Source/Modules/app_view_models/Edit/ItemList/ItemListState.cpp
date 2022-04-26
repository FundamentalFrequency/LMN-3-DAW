#include "ItemListState.h"
namespace app_view_models {

ItemListState::ItemListState(juce::ValueTree parent, int size)
    : listState(parent.getOrCreateChildWithName(IDs::LIST_STATE, nullptr)),
      listSize(size) {
    jassert(listState.hasType(IDs::LIST_STATE));
    listState.addListener(this);

    std::function<int(int)> selectedIndexConstrainer = [this](int param) {
        // selected index cannot be less than -1
        // -1 means nothing is selected
        // greater than -1 means something is selected
        // it also cannot be greater than the number of items
        if (param <= -1) {
            // can only be -1 if there are 0 items
            if (listSize > 0)
                return 0;
            else
                return -1;
        } else if (param >= listSize)
            return listSize - 1;
        else
            return param;
    };

    selectedItemIndex.setConstrainer(selectedIndexConstrainer);
    selectedItemIndex.referTo(listState, IDs::selectedItemIndex, nullptr, 0);
}

int ItemListState::getSelectedItemIndex() { return selectedItemIndex.get(); }

void ItemListState::setSelectedItemIndex(int newIndex) {
    if (newIndex != getSelectedItemIndex())
        selectedItemIndex.setValue(newIndex, nullptr);
}

void ItemListState::addListener(Listener *l) {
    listeners.add(l);
    l->selectedIndexChanged(getSelectedItemIndex());
}

void ItemListState::removeListener(Listener *l) { listeners.remove(l); }

void ItemListState::handleAsyncUpdate() {
    if (compareAndReset(shouldUpdateSelectedIndex))
        listeners.call([this](Listener &l) {
            l.selectedIndexChanged(getSelectedItemIndex());
        });
}

void ItemListState::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property) {
    if (treeWhosePropertyHasChanged == listState)
        if (property == app_view_models::IDs::selectedItemIndex)
            markAndUpdate(shouldUpdateSelectedIndex);
}

} // namespace app_view_models