#pragma once

namespace app_view_models
{

    class EditItemListViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        EditItemListViewModel(juce::ValueTree stateToListenTo, juce::ValueTree parent, juce::Array<juce::Identifier> identifiersOfInterest, EditItemListAdapter* a);
        ~EditItemListViewModel();


        EditItemListAdapter* getAdapter();

        juce::StringArray getItemNames();
        tracktion_engine::EditItem* getSelectedItem();


        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void itemsChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);


        // async update markers
        bool shouldUpdateItems = false;

    protected:

        // This is what we are interested in watching for child changes
        // ie for tracks this is the edit state
        // for plugins this is the track state
        // for modifiers this is the track state
        juce::ValueTree stateToListenToForChildChanges;
        // this is used to check for a match in child added/removed
        juce::Array<juce::Identifier> childIdentifiersOfInterest;
        EditItemListAdapter* adapter;

        juce::ListenerList<Listener> listeners;

        void handleAsyncUpdate() override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;

    public:

        ItemListState itemListState;

    };

}

