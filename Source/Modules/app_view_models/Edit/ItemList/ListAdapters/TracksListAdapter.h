#pragma once

namespace app_view_models {

class TracksListAdapter : public EditItemListAdapter {
  public:
    TracksListAdapter(tracktion::Edit &e);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion::Edit &edit;
};

} // namespace app_view_models
