#pragma once

namespace app_view_models {
namespace IDs {
const juce::Identifier EDIT_VIEW_STATE("EDIT_VIEW_STATE");
const juce::Identifier currentOctave("currentOctave");
} // namespace IDs

class EditViewModel : public juce::ValueTree::Listener,
                      public FlaggedAsyncUpdater {
  public:
    EditViewModel(tracktion::Edit &e);
    ~EditViewModel() override;

    class Listener {
      public:
        virtual ~Listener() = default;
        virtual void octaveChange(const int octave) {}
        virtual void trackDeleted() {}
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

    [[nodiscard]] int getCurrentOctave() const;
    void setCurrentOctave(int octave);

  private:
    const int MIN_OCTAVE = -4;
    const int MAX_OCTAVE = 4;
    tracktion::Edit &edit;
    // this is the EDIT_VIEW_STATE value tree that is a child of the edit
    // value tree
    juce::ValueTree state;
    juce::ListenerList<Listener> listeners;

    tracktion::ConstrainedCachedValue<int> currentOctave;

    // Async updater flags
    bool shouldUpdateOctave = false;
    bool shouldUpdateTracks = false;
    void handleAsyncUpdate() override;
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;
    void valueTreeChildRemoved(juce::ValueTree &parentTree,
                               juce::ValueTree &childWhichHasBeenRemoved,
                               int indexFromWhichChildWasRemoved) override;
};

} // namespace app_view_models
