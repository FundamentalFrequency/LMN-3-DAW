#pragma once

namespace app_view_models {
class MixerTracksListAdapter : public EditItemListAdapter {
  public:
    explicit MixerTracksListAdapter(tracktion_engine::Edit &e);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion_engine::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion_engine::Edit &edit;
};
} // namespace app_view_models
