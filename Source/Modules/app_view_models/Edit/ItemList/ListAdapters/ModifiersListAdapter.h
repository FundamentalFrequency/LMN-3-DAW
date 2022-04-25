#pragma once

namespace app_view_models {

class ModifiersListAdapter : public EditItemListAdapter {

  public:
    ModifiersListAdapter(tracktion_engine::Track::Ptr t);

    juce::StringArray getItemNames() override;
    int size() override;
    tracktion_engine::EditItem *getItemAtIndex(int index) override;

  private:
    tracktion_engine::Track::Ptr track;
};

} // namespace app_view_models
