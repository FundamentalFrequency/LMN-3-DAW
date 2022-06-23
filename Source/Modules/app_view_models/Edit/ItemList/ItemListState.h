#pragma once

namespace app_view_models {
namespace IDs {

const juce::Identifier LIST_STATE("LIST_STATE");
const juce::Identifier selectedItemIndex("selectedItemIndex");

} // namespace IDs

class ItemListState : public juce::ValueTree::Listener,
                      public FlaggedAsyncUpdater {
  public:
    ItemListState(juce::ValueTree parent, int size);

    int getSelectedItemIndex();
    void setSelectedItemIndex(int newIndex);

    class Listener {
      public:
        virtual ~Listener() = default;
        virtual void selectedIndexChanged(int newIndex) {}
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

    int listSize;

  private:
    // this stores the state of the list (the selected index)
    juce::ValueTree listState;
    tracktion::ConstrainedCachedValue<int> selectedItemIndex;
    juce::ListenerList<Listener> listeners;

    // Async update markers
    bool shouldUpdateSelectedIndex = false;

    void handleAsyncUpdate() override;
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;
};

} // namespace app_view_models
