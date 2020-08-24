#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_view_models/app_view_models.h>
#include "ClipComponent.h"

class TrackView
    : public juce::Component,
      public app_view_models::TrackViewModel::Listener
{
public:

    enum ColourIds
    {
        unselectedBackgroundColourId = 0x4000680,
        selectedBackgroundColourId = 0x4000681,
        selectedTextColourId = 0x4000682,
        unselectedTextColourId = 0x4000683
    };

    TrackView(tracktion_engine::AudioTrack& t, tracktion_engine::SelectionManager& sm);
    ~TrackView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelected(bool selected);

    void lookAndFeelChanged() override;

    void clipsChanged(const juce::Array<tracktion_engine::Clip*>& clips) override;
    void clipPositionsChanged(const juce::Array<tracktion_engine::Clip*>& clips) override;
    void transportChanged() override;

private:

    tracktion_engine::AudioTrack& track;
    tracktion_engine::SelectionManager& selectionManager;
    app_view_models::TrackViewModel viewModel;
    juce::Label titleLabel;
    juce::Colour backgroundColour;
    juce::Colour textColour;
    bool isSelected = false;

    juce::OwnedArray<ClipComponent> clips;

    void buildClips();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackView)
};

