#include "EditItemListViewModel.h"

namespace app_view_models
{

    EditItemListViewModel::EditItemListViewModel(juce::ValueTree stateToListenTo, juce::ValueTree parent,
                                                 juce::Array<juce::Identifier> identifiersOfInterest,
                                                 tracktion_engine::SelectionManager& sm, EditItemListAdapter* a)
        : stateToListenToForChildChanges(stateToListenTo),
          childIdentifiersOfInterest(identifiersOfInterest),
          listState(parent.getOrCreateChildWithName(IDs::LIST_STATE, nullptr)),
          selectionManager(sm),
          adapter(a)
    {

        jassert(listState.hasType(IDs::LIST_STATE));

        stateToListenToForChildChanges.addListener(this);
        listState.addListener(this);

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of items
            if (param <= -1)
            {
                // can only be -1 if there are 0 items
                if (adapter->size() > 0)
                    return 0;
                else
                    return -1;
            }
            else if (param >= adapter->size())
                return adapter->size() - 1;
            else
                return param;

        };

        selectedItemIndex.setConstrainer(selectedIndexConstrainer);
        selectedItemIndex.referTo(listState, IDs::selectedItemIndex, nullptr, 0);

        // set initial selection
        selectionManager.deselectAll();
        if (auto selectableItem = dynamic_cast<tracktion_engine::Selectable*>(getSelectedItem()))
            selectionManager.selectOnly(selectableItem);

    }
    EditItemListViewModel::~EditItemListViewModel()
    {

        stateToListenToForChildChanges.removeListener(this);
        listState.removeListener(this);

    }

    EditItemListAdapter* EditItemListViewModel::getAdapter()
    {

        return adapter;

    }

    int EditItemListViewModel::getSelectedItemIndex()
    {

        return selectedItemIndex.get();

    }

    void EditItemListViewModel::setSelectedItemIndex(int newIndex)
    {
        if (newIndex != getSelectedItemIndex())
            selectedItemIndex.setValue(newIndex, nullptr);

    }

    juce::StringArray EditItemListViewModel::getItemNames()
    {

        return adapter->getItemNames();

    }

    tracktion_engine::EditItem* EditItemListViewModel::getSelectedItem()
    {

        return adapter->getItemAtIndex(getSelectedItemIndex());

    }

    void EditItemListViewModel::addListener(Listener *l)
    {
        listeners.add(l);
        l->selectedIndexChanged(getSelectedItemIndex());
        l->itemsChanged();
    }

    void EditItemListViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);

    }

    void EditItemListViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            selectionManager.deselectAll();
            if (auto selectableItem = dynamic_cast<tracktion_engine::Selectable*>(getSelectedItem()))
                selectionManager.selectOnly(selectableItem);

            listeners.call([this](Listener &l) { l.selectedIndexChanged(getSelectedItemIndex()); });

        }

        if (compareAndReset(shouldUpdateItems))
        {

            selectionManager.deselectAll();
            if (auto selectableItem = dynamic_cast<tracktion_engine::Selectable*>(getSelectedItem()))
                selectionManager.selectOnly(selectableItem);

            // need to ensure selected index is not beyond the current number of items
            if (getSelectedItemIndex() >= adapter->size())
            {

                setSelectedItemIndex(adapter->size() - 1);

            }

            // if a previously empty list now has items, we need to set the selected index to 0
            if (getSelectedItemIndex() <= -1 && adapter->size() > 0)
            {

                setSelectedItemIndex(0);

            }

            listeners.call([this](Listener &l) { l.itemsChanged(); });

        }

    }

    void EditItemListViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == listState)
        {

            if (property == app_view_models::IDs::selectedItemIndex)
                markAndUpdate(shouldUpdateSelectedIndex);

        }

    }

    void EditItemListViewModel::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {


        if (parentTree == stateToListenToForChildChanges) {

            if (childIdentifiersOfInterest.contains(childWhichHasBeenAdded.getType()))
                markAndUpdate(shouldUpdateItems);

        }

    }

    void EditItemListViewModel::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

        if (parentTree == stateToListenToForChildChanges)
            if (childIdentifiersOfInterest.contains(childWhichHasBeenRemoved.getType()))
                markAndUpdate(shouldUpdateItems);

    }

}
