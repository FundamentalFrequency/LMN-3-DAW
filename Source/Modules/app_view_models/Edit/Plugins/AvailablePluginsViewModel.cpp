#include "AvailablePluginsViewModel.h"

namespace app_view_models {

    AvailablePluginsViewModel::AvailablePluginsViewModel(tracktion_engine::AudioTrack& t, tracktion_engine::SelectionManager& sm)
            : track(t),
              rootPluginTreeGroup(track.edit),
              state(track.state.getOrCreateChildWithName(IDs::AVAILABLE_PLUGINS_VIEW_STATE, nullptr)),
              selectionManager(sm)
    {

        jassert(state.hasType(app_view_models::IDs::AVAILABLE_PLUGINS_VIEW_STATE));

        // we want to subscribe to changes to the track value tree
        // this is so we can be notified when changes are made to the track
        // as well as when the AVAILABLE_INSTRUMENTS_PLUGINS_VIEW_STATE child tree changes
        track.state.addListener(this);

        std::function<int(int)> selectedCategoryIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than/equal to the number of sub items
            if (param <= -1)
            {
                // can only be -1 if there are 0 categories
                if (rootPluginTreeGroup.getNumberOfSubItems() > 0)
                    return 0;
                else
                    return -1;
            }
            else if (param >= rootPluginTreeGroup.getNumberOfSubItems())
                return rootPluginTreeGroup.getNumberOfSubItems() - 1;
            else
                return param;

        };

        selectedCategoryIndex.setConstrainer(selectedCategoryIndexConstrainer);
        selectedCategoryIndex.referTo(state, app_view_models::IDs::selectedCategoryIndex, nullptr, 0);

        std::function<int(int)> selectedPluginIndexConstrainer = [this](int param) {

            if (auto selectedCategoryPluginGroup = getSelectedCategory())
            {
                if (param <= -1)
                {
                    // can only be -1 if there are 0 plugins
                    if (selectedCategoryPluginGroup->getNumberOfSubItems() > 0)
                        return 0;
                    else
                        return -1;
                }
                else if (param >= selectedCategoryPluginGroup->getNumberOfSubItems())
                    return selectedCategoryPluginGroup->getNumberOfSubItems()  - 1;
                else
                    return param;

            } else {

                return -1;

            }


        };

        selectedPluginIndex.setConstrainer(selectedPluginIndexConstrainer);
        selectedPluginIndex.referTo(state, app_view_models::IDs::selectedPluginIndex, nullptr, 0);

        previouslySelectedInstrumentsIndex.referTo(state, app_view_models::IDs::previouslySelectedInstrumentsIndex,
                                                   nullptr, 0);
        previouslySelectedEffectsIndex.referTo(state, app_view_models::IDs::previouslySelectedEffectsIndex,
                                                   nullptr, 0);


        // category names will never change once the view model is initialized
        // we can populate them now
        for (int i = 0; i < rootPluginTreeGroup.getNumberOfSubItems(); i++)
        {

            if (auto category = dynamic_cast<PluginTreeGroup*>(rootPluginTreeGroup.getSubItem(i)))
                categoryNames.add(category->name);

        }

        // set initial selection
        selectionManager.deselectAll();
        selectionManager.selectOnly(getSelectedPlugin());

    }

    AvailablePluginsViewModel::~AvailablePluginsViewModel()
    {

        track.state.removeListener(this);

    }


    int AvailablePluginsViewModel::getSelectedCategoryIndex()
    {

        return selectedCategoryIndex.get();

    }
    void AvailablePluginsViewModel::setSelectedCategoryIndex(int newIndex)
    {

        if (newIndex != getSelectedCategoryIndex())
        {

            if (getSelectedCategory()->name == "Instruments")
                previouslySelectedInstrumentsIndex.setValue(getSelectedPluginIndex(), nullptr);
            if (getSelectedCategory()->name == "Effects")
                previouslySelectedEffectsIndex.setValue(getSelectedPluginIndex(), nullptr);

            selectedCategoryIndex.setValue(newIndex, nullptr);

        }


    }

    PluginTreeGroup* AvailablePluginsViewModel::getSelectedCategory()
    {

        if (auto group = dynamic_cast<PluginTreeGroup*>(rootPluginTreeGroup.getSubItem(getSelectedCategoryIndex())))
            return group;
        else
            return nullptr;

    }

    int AvailablePluginsViewModel::getSelectedPluginIndex()
    {

        return selectedPluginIndex.get();

    }

    void AvailablePluginsViewModel::setSelectedPluginIndex(int newIndex)
    {

        if (newIndex != getSelectedPluginIndex())
            selectedPluginIndex.setValue(newIndex, nullptr);

    }

    tracktion_engine::Plugin::Ptr AvailablePluginsViewModel::getSelectedPlugin() {

        if (selectedPluginIndex != -1)
        {
            if (auto selectedCategoryPluginGroup = getSelectedCategory())
            {
                if (auto selectedPluginItem = dynamic_cast<PluginTreeItem*>(selectedCategoryPluginGroup->getSubItem(getSelectedPluginIndex())))
                    return selectedPluginItem->create(track.edit);
                else
                    return nullptr;
            }
            else
                return nullptr;

        }
        else
            return nullptr;

    }

    juce::StringArray AvailablePluginsViewModel::getCategoryNames()
    {

        return categoryNames;

    }

    juce::StringArray AvailablePluginsViewModel::getPluginNames()
    {

        pluginNames.clear();
        if (auto selectedCategoryPluginGroup = getSelectedCategory())
        {


            for (int i = 0; i < selectedCategoryPluginGroup->getNumberOfSubItems(); i++)
            {

                if (auto plugin = dynamic_cast<PluginTreeItem*>(selectedCategoryPluginGroup->getSubItem(i)))
                    pluginNames.add(plugin->description.name);

            }

        }

        return pluginNames;

    }

    void AvailablePluginsViewModel::addSelectedPluginToTrack()
    {

        if (auto pluginToAdd = getSelectedPlugin())
        {

            bool pluginExistsInListAlready = false;
            for (auto p : track.pluginList.getPlugins())
            {
                if (p->getIdentifierString() == pluginToAdd->getIdentifierString())
                {
                    pluginExistsInListAlready = true;
                }
            }

            if (!pluginExistsInListAlready)
            {

                if (pluginToAdd->isSynth())
                {
                    // first we need to check if there is currently a synth on the track
                    if (track.pluginList.size() > 0 && track.pluginList.getPlugins()[0]->isSynth())
                        track.pluginList.getPlugins().getFirst()->removeFromParent();

                    track.pluginList.insertPlugin(pluginToAdd, 0, nullptr);

                } else {

                    track.pluginList.insertPlugin(pluginToAdd, track.pluginList.size(), nullptr);
                }

            }
        }
    }

    void AvailablePluginsViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedCategoryIndex))
        {

            // need to update the selected plugin index to what it was for the previous category
            if (getSelectedCategory()->name == "Instruments")
                setSelectedPluginIndex(previouslySelectedInstrumentsIndex.get());
            else if (getSelectedCategory()->name == "Effects")
                setSelectedPluginIndex(previouslySelectedEffectsIndex.get());
            else
                setSelectedPluginIndex(0);

            listeners.call([this](Listener &l) { l.selectedCategoryIndexChanged(getSelectedCategoryIndex()); });

        }

        if (compareAndReset(shouldUpdateSelectedPluginIndex))
        {

            selectionManager.deselectAll();
            selectionManager.selectOnly(getSelectedPlugin());

            listeners.call([this](Listener &l) { l.selectedPluginIndexChanged(getSelectedPluginIndex()); });

        }

    }

    void AvailablePluginsViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == track.state.getChildWithName(app_view_models::IDs::AVAILABLE_PLUGINS_VIEW_STATE))
        {

            if (property == app_view_models::IDs::selectedCategoryIndex)
                markAndUpdate(shouldUpdateSelectedCategoryIndex);

            if (property == app_view_models::IDs::selectedPluginIndex)
                markAndUpdate(shouldUpdateSelectedPluginIndex);

        }


    }

    void AvailablePluginsViewModel::addListener(Listener *l)
    {

        listeners.add(l);
        l->selectedCategoryIndexChanged(getSelectedCategoryIndex());
        l->selectedPluginIndexChanged(getSelectedPluginIndex());

    }

    void AvailablePluginsViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);
    }

}

