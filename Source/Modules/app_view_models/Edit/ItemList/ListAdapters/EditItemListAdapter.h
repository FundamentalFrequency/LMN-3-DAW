#pragma once

namespace app_view_models {

class EditItemListAdapter {
  public:
    virtual juce::StringArray getItemNames() = 0;
    virtual int size() = 0;
    virtual tracktion_engine::EditItem *getItemAtIndex(int index) = 0;
};

} // namespace app_view_models
