#pragma once

namespace app_view_models
{

    namespace IDs {

        const juce::Identifier LIST_STATE("LIST_STATE");
        const juce::Identifier selectedItemIndex("selectedItemIndex");

    }

    class EditItemListViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        EditItemListViewModel(juce::ValueTree stateToListenTo, juce::ValueTree parent, juce::Identifier identifierOfInterest, tracktion_engine::SelectionManager& sm, EditItemListAdapter* a);
        ~EditItemListViewModel();

        int getSelectedItemIndex();
        void setSelectedItemIndex(int newIndex);

        EditItemListAdapter* getAdapter();

        juce::StringArray getItemNames();
        tracktion_engine::EditItem* getSelectedItem();


        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedIndexChanged(int newIndex) {};
            virtual void itemsChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

        // async update markers
        bool shouldUpdateItems = false;
        bool shouldUpdateSelectedIndex = false;

    protected:

        // This is what we are interested in watching for child changes
        // ie for tracks this is the edit state
        // for plugins this is the track state
        // for modifiers this is the track state
        juce::ValueTree stateToListenToForChildChanges;
        // this is used to check for a match in child added/removed
        juce::Identifier childIdentifierOfInterest;
        // this stores the state of the list (the selected index)
        juce::ValueTree listState;
        tracktion_engine::SelectionManager& selectionManager;
        EditItemListAdapter* adapter;

        tracktion_engine::ConstrainedCachedValue<int> selectedItemIndex;

        juce::ListenerList<Listener> listeners;

        void handleAsyncUpdate() override;
        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;

    };

}

