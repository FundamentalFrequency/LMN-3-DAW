#pragma once
#include "AppLookAndFeel.h"
#include "LabeledKnob.h"
#include "LevelMeterComponent.h"
#include "SelectedTrackMarker.h"
#include <FontData.h>
#include <app_view_models/app_view_models.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

class MixerTrackView : public juce::Component,
                       public app_view_models::MixerTrackViewModel::Listener {
  public:
    MixerTrackView(tracktion::Track::Ptr t);
    ~MixerTrackView();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void setSelected(bool selected);

    void panChanged(double pan) override;
    void volumeChanged(double volume) override;
    void soloStateChanged(bool solo) override;
    void muteStateChanged(bool mute) override;

  private:
    tracktion::Track::Ptr track;
    app_view_models::MixerTrackViewModel viewModel;
    bool isSelected = false;
    LabeledKnob panKnob;
    juce::Slider volumeSlider;
    juce::Grid grid;
    std::unique_ptr<LevelMeterComponent> levelMeter0;
    std::unique_ptr<LevelMeterComponent> levelMeter1;

    juce::Typeface::Ptr faTypeface = juce::Typeface::createSystemTypefaceFor(
        FontData::FontAwesome6FreeSolid900_otf,
        FontData::FontAwesome6FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(faTypeface);
    juce::Label soloLabel;
    juce::Label muteLabel;

    AppLookAndFeel appLookAndFeel;

    SelectedTrackMarker selectionShroud;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerTrackView)
};
