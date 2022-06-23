#pragma once

namespace app_view_models {

class PluginsListAdapter : public EditItemListAdapter {
  public:
    PluginsListAdapter(tracktion::Track::Ptr t);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion::Track::Ptr track;
};

} // namespace app_view_models
