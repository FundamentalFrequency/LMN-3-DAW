#include "FilterView.h"

FilterView::FilterView(tracktion_engine::FourOscPlugin *p,
                       app_services::MidiCommandManager &mcm)
    : viewModel(p), midiCommandManager(mcm),
      filterAdsrView(p, midiCommandManager) {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: Filter", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    addChildComponent(filterAdsrView);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 2;

    for (int i = 0; i < numRows; i++)
        grid.templateRows.add(Track(Fr(1)));

    for (int j = 0; j < numCols; j++)
        grid.templateColumns.add(Track(Fr(1)));

    for (int i = 0; i < 4; i++) {
        knobs.add(new LabeledKnob());

        if (i == 0 || i == 8) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour1);
        }

        if (i == 1 || i == 9) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour2);
        }

        if (i == 2 || i == 10) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour3);
        }

        if (i == 3 || i == 11) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour4);
        }

        if (i == 4 || i == 12) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour5);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour5);
        }

        if (i == 5 || i == 13) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour6);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour6);
        }

        if (i == 6 || i == 14) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour7);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour7);
        }

        if (i == 7 || i == 15) {
            knobs[i]->getSlider().setColour(
                juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour8);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                            appLookAndFeel.colour8);
        }

        if (i < 8) {
            grid.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        }
    }

    knobs[0]->getLabel().setText("Frequency", juce::dontSendNotification);
    knobs[0]->getSlider().setRange(viewModel.filterNormRange.getRange(), 0);
    knobs[0]->getSlider().setSkewFactor(viewModel.filterNormRange.skew);
    knobs[0]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[1]->getLabel().setText("Resonance", juce::dontSendNotification);
    knobs[1]->getSlider().setRange(0, 1, 0);
    knobs[1]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[2]->getLabel().setText("Envelope Amount", juce::dontSendNotification);
    knobs[2]->getSlider().setRange(0, 1, 0);
    knobs[2]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[3]->getLabel().setText("Filter Type", juce::dontSendNotification);
    knobs[3]->getSlider().setRange(0, 4, 1);

    // now we need to fill out the remaining disabled knobs
    for (int i = 4; i < 8; i++) {
        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("", juce::dontSendNotification);
        knobs[i]->getSlider().setEnabled(false);
        knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId,
                                        juce::Colours::grey);
        knobs[i]->getSlider().setColour(juce::Slider::thumbColourId,
                                        juce::Colours::grey);

        grid.items.add(juce::GridItem(knobs[i]));
        addAndMakeVisible(knobs[i]);
    }

    midiCommandManager.addListener(this);
    viewModel.addListener(this);
}

FilterView::~FilterView() {
    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
}

void FilterView::paint(juce::Graphics &g) {}

void FilterView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .05, getWidth(), getHeight() * .1);

    filterAdsrView.setBounds(getLocalBounds());

    gridSetup();
}

void FilterView::gridSetup() {
    int widthPadding = getWidth() * .05;
    int heightPadding = getHeight() * .05;

    grid.setGap(juce::Grid::Px(heightPadding));

    int startX = widthPadding;
    int startY = titleLabel.getY() + titleLabel.getHeight() + (heightPadding);
    int width = getWidth() - (2 * widthPadding);
    int height = (getHeight() - startY) - (heightPadding);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid.performLayout(bounds);
}

void FilterView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.incrementAttack();
            else
                viewModel.incrementFrequency();
        }
    }
}

void FilterView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.decrementAttack();
            else
                viewModel.decrementFrequency();
        }
    }
}

void FilterView::encoder2Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.incrementDecay();
            else
                viewModel.incrementResonance();
        }
    }
}

void FilterView::encoder2Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.decrementDecay();
            else
                viewModel.decrementResonance();
        }
    }
}

void FilterView::encoder3Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.incrementSustain();
            else
                viewModel.incrementEnvelopeAmount();
        }
    }
}

void FilterView::encoder3Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.decrementSustain();
            else
                viewModel.decrementEnvelopeAmount();
        }
    }
}

void FilterView::encoder4Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.incrementRelease();
            else
                viewModel.incrementFilterType();
        }
    }
}

void FilterView::encoder4Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown)
                viewModel.decrementRelease();
            else
                viewModel.decrementFilterType();
        }
    }
}

void FilterView::shiftButtonPressed() {
    filterAdsrView.setVisible(true);

    for (int i = 0; i < 8; i++)
        knobs[i]->setVisible(false);
}

void FilterView::shiftButtonReleased() {
    filterAdsrView.setVisible(false);
    for (int i = 0; i < 8; i++)
        knobs[i]->setVisible(true);
}

void FilterView::parametersChanged() {
    knobs[0]->getSlider().setValue(viewModel.getFrequency(),
                                   juce::dontSendNotification);
    knobs[1]->getSlider().setValue(viewModel.getResonance(),
                                   juce::dontSendNotification);
    knobs[2]->getSlider().setValue(viewModel.getEnvelopeAmount(),
                                   juce::dontSendNotification);
    knobs[3]->getSlider().setValue(viewModel.getFilterType(),
                                   juce::dontSendNotification);
}
