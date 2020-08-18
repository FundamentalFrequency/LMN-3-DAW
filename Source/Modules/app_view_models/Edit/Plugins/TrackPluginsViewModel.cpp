#include "TrackPluginsViewModel.h"

namespace app_view_models {

    TrackPluginsViewModel::TrackPluginsViewModel(tracktion_engine::Track& t, app_services::MidiCommandManager& mcm, tracktion_engine::SelectionManager& sm)
            : track(t),
              state(track.state.getOrCreateChildWithName(IDs::TRACK_PLUGINS_VIEW_STATE, nullptr)),
              midiCommandManager(mcm),
              selectionManager(sm)
    {

        jassert(state.hasType(app_view_models::IDs::TRACK_PLUGINS_VIEW_STATE));

        // we want to subscribe to changes to the track value tree
        // this is so we can be notified when changes are made to the track
        // as well as when the TRACK_PLUGINS_VIEW_STATE child tree changes
        track.state.addListener(this);
        midiCommandManager.addListener(this);

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of tracks
            if (param <= -1)
            {
                // can only be -1 if there are 0 audio tracks
                if (track.getAllPlugins().size() > 0)
                    return 0;
                else
                    return -1;
            }
            else if (param >= track.getAllPlugins().size() )
                return track.getAllPlugins().size()  - 1;
            else
                return param;

        };

        selectedPluginIndex.setConstrainer(selectedIndexConstrainer);
        selectedPluginIndex.referTo(state, app_view_models::IDs::selectedPluginIndex, nullptr, 0);

        // set initial selection
        selectionManager.deselectAll();
        selectionManager.selectOnly(getSelectedPlugin());
    }

    TrackPluginsViewModel::~TrackPluginsViewModel() {

        track.state.removeListener(this);
        midiCommandManager.removeListener(this);
    }


    int TrackPluginsViewModel::getSelectedPluginIndex() {


        return selectedPluginIndex.get();

    }

    void TrackPluginsViewModel::setSelectedPluginIndex(int newIndex)
    {

        if (newIndex != getSelectedPluginIndex())
            selectedPluginIndex.setValue(newIndex, nullptr);

    }

    tracktion_engine::Plugin* TrackPluginsViewModel::getSelectedPlugin() {

        if (selectedPluginIndex != -1)
            return track.getAllPlugins().getObjectPointerUnchecked(selectedPluginIndex);
        else
            return nullptr;

    }

    void TrackPluginsViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            selectionManager.deselectAll();
            selectionManager.selectOnly(getSelectedPlugin());
            DBG("selecting plugin at index: " + juce::String(getSelectedPluginIndex()));
            listeners.call([this](Listener &l) { l.selectedPluginIndexChanged(getSelectedPluginIndex()); });

        }

        if (compareAndReset(shouldUpdatePlugins))
        {
            // tracks changed
            // need to ensure selected index is not beyond the current number of tracks
            if (getSelectedPluginIndex() >= track.getAllPlugins().size())
            {

                setSelectedPluginIndex(track.getAllPlugins().size() - 1);

            }

            // if a previously empty edit now has tracks, we need to set the selected index to 0
            if (getSelectedPluginIndex() <= -1 && track.getAllPlugins().size() > 0)
            {

                setSelectedPluginIndex(0);

            }

            listeners.call([this](Listener &l) { l.pluginsChanged(); });

        }
    }

    void TrackPluginsViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == track.state.getChildWithName(app_view_models::IDs::TRACK_PLUGINS_VIEW_STATE))
        {

            if (property == app_view_models::IDs::selectedPluginIndex)
                markAndUpdate(shouldUpdateSelectedIndex);

        }


    }

    void TrackPluginsViewModel::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {

        if (childWhichHasBeenAdded.hasType(tracktion_engine::IDs::PLUGIN)) {

            markAndUpdate(shouldUpdatePlugins);
        }


    }

    void TrackPluginsViewModel::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

        if (childWhichHasBeenRemoved.hasType(tracktion_engine::IDs::PLUGIN))
            markAndUpdate(shouldUpdatePlugins);

    }

    void TrackPluginsViewModel::addListener(Listener *l)
    {

        listeners.add(l);

    }

    void TrackPluginsViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);
    }

    void TrackPluginsViewModel::encoder1Increased()
    {
        if (getSelectedPluginIndex() != track.getAllPlugins().size() - 1)
            setSelectedPluginIndex(getSelectedPluginIndex() + 1);
    }

    void TrackPluginsViewModel::encoder1Decreased()
    {
        if (getSelectedPluginIndex() != 0)
            setSelectedPluginIndex(getSelectedPluginIndex() - 1);
    }

    void TrackPluginsViewModel::encoder1ButtonReleased()
    {

    }

}

