#include "FilterView.h"

FilterView::FilterView(tracktion_engine::FourOscPlugin *p,
                       app_services::MidiCommandManager &mcm)
    : viewModel(p), midiCommandManager(mcm), knobs(8), filterAdsrView(p, midiCommandManager) {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: Filter", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    addChildComponent(filterAdsrView);

    knobs.getKnob(0)->getLabel().setText("Frequency", juce::dontSendNotification);
    knobs.getKnob(0)->getSlider().setRange(viewModel.getFrequencyRange().getStart(),
                                   viewModel.getFrequencyRange().getEnd(), 0);
    knobs.getKnob(0)->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs.getKnob(1)->getLabel().setText("Resonance", juce::dontSendNotification);
    knobs.getKnob(1)->getSlider().setRange(0, 1, 0);
    knobs.getKnob(1)->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs.getKnob(2)->getLabel().setText("Envelope Amount", juce::dontSendNotification);
    knobs.getKnob(2)->getSlider().setRange(0, 1, 0);
    knobs.getKnob(2)->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs.getKnob(3)->getLabel().setText("Filter Type", juce::dontSendNotification);
    knobs.getKnob(3)->getSlider().setRange(0, 4, 1);

    addAndMakeVisible(knobs);

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

    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;
    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);
    juce::Rectangle<int> bounds(startX, startY, width, height);
    knobs.setGridSpacing(knobSpacing);
    knobs.setBounds(bounds);
}


void FilterView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.incrementAttack();
            else
                viewModel.incrementFrequency();
        }
    }
}

void FilterView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.decrementAttack();
            else
                viewModel.decrementFrequency();
        }
    }
}

void FilterView::encoder2Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.incrementDecay();
            else
                viewModel.incrementResonance();
        }
    }
}

void FilterView::encoder2Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.decrementDecay();
            else
                viewModel.decrementResonance();
        }
    }
}

void FilterView::encoder3Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.incrementSustain();
            else
                viewModel.incrementEnvelopeAmount();
        }
    }
}

void FilterView::encoder3Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.decrementSustain();
            else
                viewModel.decrementEnvelopeAmount();
        }
    }
}

void FilterView::encoder4Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.incrementRelease();
            else
                viewModel.incrementFilterType();
        }
    }
}

void FilterView::encoder4Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isControlDown)
                viewModel.decrementRelease();
            else
                viewModel.decrementFilterType();
        }
    }
}

void FilterView::controlButtonPressed() {
    filterAdsrView.setVisible(true);
    knobs.setVisible(false);
}

void FilterView::controlButtonReleased() {
    filterAdsrView.setVisible(false);
    knobs.setVisible(true);
}

void FilterView::parametersChanged() {
    knobs.getKnob(0)->getSlider().setValue(viewModel.getFrequency(),
                                   juce::dontSendNotification);
    knobs.getKnob(1)->getSlider().setValue(viewModel.getResonance(),
                                   juce::dontSendNotification);
    knobs.getKnob(2)->getSlider().setValue(viewModel.getEnvelopeAmount(),
                                   juce::dontSendNotification);
    knobs.getKnob(3)->getSlider().setValue(viewModel.getFilterType(),
                                   juce::dontSendNotification);
}
