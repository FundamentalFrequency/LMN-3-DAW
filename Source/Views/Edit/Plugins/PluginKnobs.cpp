#include "PluginKnobs.h"
PluginKnobs::PluginKnobs(int numEnabledParameters) {
    this->numEnabledParameters = numEnabledParameters;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 1;

    for (int i = 0; i < numRows; i++) {
        grid1.templateRows.add(Track(Fr(1)));
        grid2.templateRows.add(Track(Fr(1)));
    }

    for (int j = 0; j < numCols; j++) {
        grid1.templateColumns.add(Track(Fr(1)));
        grid2.templateColumns.add(Track(Fr(1)));
    }

    for (int i = 0; i < numEnabledParameters; i++) {
        knobs.add(new LabeledKnob());

        if (i == 0 || i == 4) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour1);
        }

        if (i == 1 || i == 5) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour2);
        }

        if (i == 2 || i == 6) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);
        }

        if (i == 3 || i == 7) {
            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour4);
        }

        if (i < 4) {
            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        } else {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);
        }
    }

    // now we need to fill out the remaining disabled knobs
    for (int i = numEnabledParameters; i < 8; i++) {
        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("", juce::dontSendNotification);
        knobs[i]->getSlider().setEnabled(false);
        knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
        knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, juce::Colours::grey);

        if (i < 4) {
            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        } else {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);
        }
    }
}

LabeledKnob* PluginKnobs::getKnob(int knobIndex) {
    return knobs[knobIndex];
}


void PluginKnobs::resized() {
    gridSetup();
}

void PluginKnobs::setGridSpacing(int spacing) {
    grid1.setGap(juce::Grid::Px(spacing));
    grid2.setGap(juce::Grid::Px(spacing));
    resized();
}

void PluginKnobs::gridSetup() {
    juce::Rectangle<int> bounds(0, 0, getWidth(), getHeight());
    grid1.performLayout(bounds);
    grid2.performLayout(bounds);
}

void PluginKnobs::setKnobValue(int knobIndex, double newValue) {
    knobs[knobIndex]->getSlider().setValue(newValue, juce::dontSendNotification);
}

void PluginKnobs::showPrimaryKnobs() {
    if (numEnabledParameters > 4) {
        for (int i = 0; i < knobs.size(); i++) {
            if (i < 4) {
                knobs[i]->setVisible(true);
            } else {
                knobs[i]->setVisible(false);
            }
        }
    }
}

void PluginKnobs::showSecondaryKnobs() {
    if (numEnabledParameters > 4) {
        for (int i = 0; i < knobs.size(); i++) {
            if (i < 4)
                knobs[i]->setVisible(false);
            else
                knobs[i]->setVisible(true);
        }
    }
}
