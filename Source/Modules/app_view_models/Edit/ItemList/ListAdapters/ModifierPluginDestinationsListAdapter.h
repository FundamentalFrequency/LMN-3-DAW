#pragma once

namespace app_view_models {

class ModifierPluginDestinationsListAdapter : public EditItemListAdapter {
  public:
    ModifierPluginDestinationsListAdapter(tracktion::Track::Ptr t);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion::Track::Ptr track;
};

} // namespace app_view_models
