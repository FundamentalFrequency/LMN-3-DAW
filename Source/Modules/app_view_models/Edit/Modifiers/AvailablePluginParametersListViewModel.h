#pragma once

namespace app_view_models {

namespace IDs {

const juce::Identifier AVAILABLE_PLUGIN_PARAMETERS_LIST_VIEW_STATE(
    "AVAILABLE_PLUGIN_PARAMETERS_LIST_VIEW_STATE");

}

class AvailablePluginParametersListViewModel {
  public:
    AvailablePluginParametersListViewModel(tracktion::AudioTrack::Ptr t,
                                           tracktion::Plugin::Ptr p);

    juce::StringArray getItemNames();
    tracktion::AutomatableParameter::Ptr getSelectedItem();

    tracktion::Modifier *
    addModifierToSelectedParameter(juce::Identifier modifierID);

  private:
    tracktion::AudioTrack::Ptr track;
    tracktion::Plugin::Ptr plugin;
    juce::ValueTree state;

  public:
    ItemListState itemListState;
};

} // namespace app_view_models
