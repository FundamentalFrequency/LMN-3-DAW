#pragma once

namespace app_view_models {

class ModifierPluginDestinationsListAdapter : public EditItemListAdapter {
  public:
    ModifierPluginDestinationsListAdapter(tracktion_engine::Track::Ptr t);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion_engine::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion_engine::Track::Ptr track;
};

} // namespace app_view_models
