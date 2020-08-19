#pragma once

namespace app_view_models {


    namespace IDs {

        const juce::Identifier TRACK_PLUGINS_VIEW_STATE("TRACK_PLUGINS_VIEW_STATE");
        const juce::Identifier selectedPluginIndex("selectedPluginIndex");

    }

    class TrackPluginsViewModel
            : public juce::ValueTree::Listener,
              public FlaggedAsyncUpdater,
              public app_services::MidiCommandManager::Listener
    {

    public:

        TrackPluginsViewModel(tracktion_engine::AudioTrack& t, tracktion_engine::SelectionManager& sm);
        ~TrackPluginsViewModel();

        int getSelectedPluginIndex();
        void setSelectedPluginIndex(int newIndex);

        tracktion_engine::Plugin* getSelectedPlugin();

        juce::ReferenceCountedArray<tracktion_engine::Plugin> getPlugins();

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void selectedPluginIndexChanged(int newIndex) {};
            virtual void pluginsChanged() {};

        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::AudioTrack& track;
        // this is the TRACKS_VIEW_STATE value tree that is a child of the edit value tree
        juce::ValueTree state;
        tracktion_engine::SelectionManager& selectionManager;
        tracktion_engine::ConstrainedCachedValue<int> selectedPluginIndex;
        juce::ListenerList<Listener> listeners;

        // async update markers
        bool shouldUpdatePlugins = false;
        bool shouldUpdateSelectedIndex = false;

        void handleAsyncUpdate() override;

        void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
        void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override;
        void valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;

    };

}



