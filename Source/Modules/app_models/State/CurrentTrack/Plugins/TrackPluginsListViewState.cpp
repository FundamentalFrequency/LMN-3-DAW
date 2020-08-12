namespace app_models {

    TrackPluginsListViewState::TrackPluginsListViewState(const juce::ValueTree &v)
        : state(v),
          selectedPluginIndex(state, IDs::selectedPluginIndex, nullptr)
    {

        jassert(v.hasType(IDs::TRACK_PLUGINS_LIST_VIEW_STATE));


    }

    int TrackPluginsListViewState::getSelectedPluginIndex()
    {

        return selectedPluginIndex.get();

    }

    void TrackPluginsListViewState::setSelectedPluginIndex(int newIndex)
    {

        selectedPluginIndex.setValue(newIndex, nullptr);
        listeners.call([this](Listener &l) { l.selectedPluginIndexChanged(getSelectedPluginIndex()); });

    }

    void TrackPluginsListViewState::addListener(TrackPluginsListViewState::Listener *l) {

        listeners.add(l);

    }

    void TrackPluginsListViewState::removeListener(TrackPluginsListViewState::Listener *l) {

        listeners.remove(l);
    }


}