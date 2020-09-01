#pragma once

namespace app_view_models
{

    namespace IDs
    {

        const juce::Identifier PLUGINS_LIST_VIEW_STATE("PLUGINS_LIST_VIEW_STATE");

    }

    class TrackPluginsListViewModel
    {

    public:

        TrackPluginsListViewModel(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::SelectionManager& sm);

        void deleteSelectedPlugin();

    private:
        tracktion_engine::AudioTrack::Ptr track;
        juce::ValueTree state;
        tracktion_engine::SelectionManager& selectionManager;
        std::unique_ptr<PluginsListAdapter> adapter;

    public:

        // Must appear below the other variables since it needs to be initialized last
        EditItemListViewModel listViewModel;

    };

}



