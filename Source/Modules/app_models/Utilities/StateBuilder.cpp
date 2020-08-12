namespace app_models
{

    juce::ValueTree StateBuilder::createThemes() {

        ThemeReader themeManager;
        return themeManager.getThemes();

    }

    juce::ValueTree StateBuilder::createTrackPluginsListViewState()
    {

        int initialSelectedPluginIndex = -1;
        juce::ValueTree trackPluginsListViewState(IDs::TRACK_PLUGINS_LIST_VIEW_STATE);
        trackPluginsListViewState.setProperty(IDs::selectedPluginIndex, initialSelectedPluginIndex, nullptr);

        return trackPluginsListViewState;

    }

    juce::ValueTree StateBuilder::createInitialStateTree() {

        juce::ValueTree state(IDs::APP_STATE);
        state.addChild(createThemes(), -1, nullptr);
        state.addChild(createTrackPluginsListViewState(), -1, nullptr);
        return state;

    }

}


