#include "LowPassPluginView.h"

LowPassPluginView::LowPassPluginView(tracktion::LowPassPlugin *p,
                                     app_services::MidiCommandManager &mcm)
    : viewModel(p), midiCommandManager(mcm) {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setText("LPF/HPF", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 1;

    for (int i = 0; i < numRows; i++)
        grid.templateRows.add(Track(Fr(1)));

    for (int j = 0; j < numCols; j++)
        grid.templateColumns.add(Track(Fr(1)));

    frequencyKnob.getSlider().setColour(juce::Slider::rotarySliderFillColourId,
                                        appLookAndFeel.colour1);
    frequencyKnob.getSlider().setColour(juce::Slider::thumbColourId,
                                        appLookAndFeel.colour1);
    frequencyKnob.getLabel().setText("Frequency (Hz)",
                                     juce::dontSendNotification);
    frequencyKnob.getSlider().setRange(
        viewModel.normRange.getRange().getStart(),
        viewModel.normRange.getRange().getEnd());
    frequencyKnob.getSlider().setSkewFactor(viewModel.normRange.skew);
    frequencyKnob.getSlider().setNumDecimalPlacesToDisplay(2);

    modeLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour2);
    modeLabel.setJustificationType(juce::Justification::centred);

    grid.items.add(frequencyKnob);
    addAndMakeVisible(frequencyKnob);

    grid.items.add(modeLabel);
    addAndMakeVisible(modeLabel);

    // now we need to fill out the remaining disabled knobs
    for (int i = 2; i < 4; i++) {
        knobs.add(new LabeledKnob());
        knobs.getLast()->getLabel().setText("", juce::dontSendNotification);
        knobs.getLast()->getSlider().setEnabled(false);
        knobs.getLast()->getSlider().setColour(
            juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
        knobs.getLast()->getSlider().setColour(juce::Slider::thumbColourId,
                                               juce::Colours::grey);
        grid.items.add(juce::GridItem(knobs.getLast()));
        addAndMakeVisible(knobs.getLast());
    }

    viewModel.addListener(this);
    midiCommandManager.addListener(this);
}

LowPassPluginView::~LowPassPluginView() {
    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);
}

void LowPassPluginView::paint(juce::Graphics &g) {}
void LowPassPluginView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    modeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                 getHeight() * .05, juce::Font::plain));

    gridSetup();
}

void LowPassPluginView::encoder1Increased() { viewModel.incrementFrequency(); }

void LowPassPluginView::encoder1Decreased() { viewModel.decrementFrequency(); }

void LowPassPluginView::encoder2Increased() {
    viewModel.setIsLowPass(!viewModel.getIsLowPass());
}

void LowPassPluginView::encoder2Decreased() {
    viewModel.setIsLowPass(!viewModel.getIsLowPass());
}

void LowPassPluginView::parametersChanged() {
    frequencyKnob.getSlider().setValue(viewModel.getFrequency(),
                                       juce::dontSendNotification);

    if (viewModel.getIsLowPass())
        modeLabel.setText("LPF", juce::dontSendNotification);
    else
        modeLabel.setText("HPF", juce::dontSendNotification);
}

void LowPassPluginView::gridSetup() {
    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;
    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);
    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid.performLayout(bounds);
}