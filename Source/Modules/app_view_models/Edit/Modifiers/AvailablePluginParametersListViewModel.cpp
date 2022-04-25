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

    tracktion_engine::Modifier* AvailablePluginParametersListViewModel::addModifierToSelectedParameter(juce::Identifier modifierID)
    {

        if (auto pluginParameter = getSelectedItem())
        {

            auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierID), -1, nullptr);
            if (auto lfoModifier = dynamic_cast<tracktion_engine::LFOModifier*>(modifier.get()))
                lfoModifier->wave.setValue(1, nullptr);
            pluginParameter->addModifier(*modifier);
            return modifier;

        }

        return nullptr;

    }

}