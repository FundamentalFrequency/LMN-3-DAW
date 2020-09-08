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

    void AvailablePluginParametersListViewModel::addModifierToSelectedParameter(juce::Identifier modifierID)
    {

        if (modifierID == tracktion_engine::IDs::LFO) {

            auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierID), -1, nullptr);
            auto lfoModifier = dynamic_cast<tracktion_engine::LFOModifier *>(modifier.get());
            // set default modifier parameters here
            lfoModifier->rateParam->setParameter(3, juce::dontSendNotification);
            auto pluginParameter = getSelectedItem();
            pluginParameter->addModifier(*modifier);


        }

        if (modifierID == tracktion_engine::IDs::STEP) {

            auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierID), -1, nullptr);
            auto stepModifier = dynamic_cast<tracktion_engine::StepModifier *>(modifier.get());
            // set default modifier parameters here
            auto pluginParameter = getSelectedItem();
            pluginParameter->addModifier(*modifier);

        }

        if (modifierID == tracktion_engine::IDs::RANDOM) {

            auto modifier = track->getModifierList().insertModifier(juce::ValueTree(modifierID), -1, nullptr);
            auto randomModifier = dynamic_cast<tracktion_engine::RandomModifier *>(modifier.get());
            // set default modifier parameters here
            auto pluginParameter = getSelectedItem();
            pluginParameter->addModifier(*modifier);

        }

    }

}