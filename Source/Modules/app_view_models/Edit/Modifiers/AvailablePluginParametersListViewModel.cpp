#include "AvailablePluginParametersListViewModel.h"

namespace app_view_models
{

    AvailablePluginParametersListViewModel::AvailablePluginParametersListViewModel(tracktion_engine::AudioTrack::Ptr t,
                                                                                  tracktion_engine::Plugin::Ptr p)
        : track(t),
          plugin(p),
          state(track->state.getOrCreateChildWithName(IDs::AVAILABLE_PLUGIN_PARAMETERS_LIST_VIEW_STATE, nullptr)),
          itemListState(state, plugin->getAutomatableParameters().size())
    {

    }

    juce::StringArray AvailablePluginParametersListViewModel::getItemNames()
    {

        juce::StringArray itemNames;
        for (auto parameter : plugin->getAutomatableParameters())
            itemNames.add(parameter->getParameterName());

        return itemNames;

    }

    tracktion_engine::AutomatableParameter::Ptr AvailablePluginParametersListViewModel::getSelectedItem()
    {

        return plugin->getAutomatableParameters()[itemListState.getSelectedItemIndex()];

    }

}