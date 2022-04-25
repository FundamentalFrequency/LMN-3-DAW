#pragma once

namespace app_view_models
{

    namespace IDs
    {

        const juce::Identifier AVAILABLE_PLUGIN_PARAMETERS_LIST_VIEW_STATE("AVAILABLE_PLUGIN_PARAMETERS_LIST_VIEW_STATE");

    }

    class AvailablePluginParametersListViewModel
    {

    public:

        AvailablePluginParametersListViewModel(tracktion_engine::AudioTrack::Ptr t, tracktion_engine::Plugin::Ptr p);

        juce::StringArray getItemNames();
        tracktion_engine::AutomatableParameter::Ptr getSelectedItem();

        tracktion_engine::Modifier* addModifierToSelectedParameter(juce::Identifier modifierID);

    private:
        tracktion_engine::AudioTrack::Ptr track;
        tracktion_engine::Plugin::Ptr plugin;
        juce::ValueTree state;

    public:
        ItemListState itemListState;

    };

}



