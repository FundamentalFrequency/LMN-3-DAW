namespace app_models {

    TrackPluginsListViewState::TrackPluginsListViewState(const juce::ValueTree &v)
        : state(v)
    {

        jassert(v.hasType(IDs::TRACK_PLUGINS_LIST_VIEW_STATE));

        std::function<int(int)> selectedIndexConstrainer = [](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            if (param < -1)
                return -1;
            else
                return param;

        };

        selectedPluginIndex.setConstrainer(selectedIndexConstrainer);
        selectedPluginIndex.referTo(state, IDs::selectedPluginIndex, nullptr);


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