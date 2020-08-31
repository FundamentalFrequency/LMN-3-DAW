#pragma once

namespace app_view_models {

    namespace IDs {

        const juce::Identifier TRACK_MODIFIERS_VIEW_STATE("TRACK_MODIFIERS_VIEW_STATE");
        const juce::Identifier selectedModifierIndex("selectedModifierIndex");

    }

    class TrackModifiersViewModel
        : public juce::ValueTree::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        TrackModifiersViewModel(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::SelectionManager& sm);
        ~TrackModifiersViewModel();

        int getSelectedModifierIndex();
        void setSelectedModifierIndex(int newIndex);

        void deleteSelectedModifier();

        tracktion_engine::Modifier::Ptr getSelectedModifier();

        juce::StringArray getModifierNames();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedModifierIndexChanged(int newIndex) {};
            virtual void modifiersChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:
        tracktion_engine::AudioTrack::Ptr track;
        // this is the TRACK_MODIFIERS_VIEW_STATE value tree that is a child of the track value tree
        juce::ValueTree state;
        tracktion_engine::SelectionManager& selectionManager;
        tracktion_engine::ConstrainedCachedValue<int> selectedModifierIndex;
        juce::ListenerList<Listener> listeners;

        juce::StringArray modifierNames;

        // async update markers
        bool shouldUpdateModifiers = false;
        bool shouldUpdateSelectedIndex = false;

        void handleAsyncUpdate() override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;


    };

}
