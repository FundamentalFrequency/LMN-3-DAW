#pragma once
#include <juce_core/juce_core.h>

namespace app_view_models {
class PluginTreeBase {
  public:
    virtual ~PluginTreeBase() = default;

    virtual juce::String getUniqueName() const = 0;

    void addSubItem(PluginTreeBase *item);

    int getNumberOfSubItems();

    PluginTreeBase *getSubItem(int index);

  private:
    juce::OwnedArray<PluginTreeBase> subItems;
};
} // namespace app_view_models
