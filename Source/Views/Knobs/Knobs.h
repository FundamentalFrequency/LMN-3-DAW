#pragma once
#include "AppLookAndFeel.h"
#include "LabeledKnob.h"
#include "Modules/app_view_models/app_view_models.h"
#include "juce_gui_basics/juce_gui_basics.h"

class Knobs : public juce::Component {
  public:
    explicit Knobs(int numEnabledParameters);
    ~Knobs() override = default;
    void resized() override;
    void setGridSpacing(int spacing);
    LabeledKnob *getKnob(int knobIndex);
    void setKnobValue(int knobIndex, double newValue);
    void showPrimaryKnobs();
    void showSecondaryKnobs();

  private:
    int numEnabledParameters = 0;
    juce::OwnedArray<LabeledKnob> knobs;
    AppLookAndFeel appLookAndFeel;

    juce::Grid grid1;
    juce::Grid grid2;
    void gridSetup();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knobs)
};
