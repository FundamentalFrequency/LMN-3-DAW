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

        EditItemListViewModel(juce::ValueTree parentState, juce::Identifier identifierOfInterest, tracktion_engine::SelectionManager& sm, EditItemListAdapter* a);
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
        juce::ValueTree listParentState;
        // this is used to check for a match in child added/removed
        juce::Identifier childIdentifierOfInterest;
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

