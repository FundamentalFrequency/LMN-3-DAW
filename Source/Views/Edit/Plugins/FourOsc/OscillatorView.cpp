#include "OscillatorView.h"

OscillatorView::OscillatorView(tracktion_engine::FourOscPlugin* p, int oscIndex, app_services::MidiCommandManager& mcm)
: viewModel(p, oscIndex),
  midiCommandManager(mcm),
  pluginKnobs(8){
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: OSC " + juce::String(oscIndex + 1), juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    pluginKnobs.getKnob(0)->getLabel().setText("Wave Shape", juce::dontSendNotification);
    pluginKnobs.getKnob(0)->getSlider().setRange(0, 6, 1);

    pluginKnobs.getKnob(1)->getLabel().setText("Voices", juce::dontSendNotification);
    pluginKnobs.getKnob(1)->getSlider().setRange(1, 8, 1);

    pluginKnobs.getKnob(2)->getLabel().setText("Tune", juce::dontSendNotification);
    pluginKnobs.getKnob(2)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(2)->getSlider().setNumDecimalPlacesToDisplay(2);

    pluginKnobs.getKnob(3)->getLabel().setText("Fine Tune", juce::dontSendNotification);
    pluginKnobs.getKnob(3)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(3)->getSlider().setNumDecimalPlacesToDisplay(2);

    pluginKnobs.getKnob(4)->getLabel().setText("Detune", juce::dontSendNotification);
    pluginKnobs.getKnob(4)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(4)->getSlider().setNumDecimalPlacesToDisplay(2);

    pluginKnobs.getKnob(5)->getLabel().setText("Level", juce::dontSendNotification);
    pluginKnobs.getKnob(5)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(5)->getSlider().setNumDecimalPlacesToDisplay(2);

    pluginKnobs.getKnob(6)->getLabel().setText("Pulse Width", juce::dontSendNotification);
    pluginKnobs.getKnob(6)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(6)->getSlider().setNumDecimalPlacesToDisplay(2);

    pluginKnobs.getKnob(7)->getLabel().setText("Spread", juce::dontSendNotification);
    pluginKnobs.getKnob(7)->getSlider().setRange(0, 1, 0);
    pluginKnobs.getKnob(7)->getSlider().setNumDecimalPlacesToDisplay(2);

    addAndMakeVisible(pluginKnobs);

    midiCommandManager.addListener(this);
    viewModel.addListener(this);
}

OscillatorView::~OscillatorView() {
    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
}

void OscillatorView::paint(juce::Graphics& g) {
}

void OscillatorView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .05, getWidth(), getHeight() * .1);

    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;
    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);
    juce::Rectangle<int> bounds(startX, startY, width, height);
    pluginKnobs.setGridSpacing(knobSpacing);
    pluginKnobs.setBounds(bounds);
}

void OscillatorView::encoder1Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.incrementDetune();
            } else {
                viewModel.incrementWaveShape();
            }
        }
    }
}

void OscillatorView::encoder1Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.decrementDetune();
            } else {
                viewModel.decrementWaveShape();
            }
        }
    }
}

void OscillatorView::encoder2Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.incrementLevel();
            } else {
                viewModel.incrementVoices();
            }
        }
    }
}

void OscillatorView::encoder2Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.decrementLevel();
            } else {
                viewModel.decrementVoices();
            }
        }
    }
}


void OscillatorView::encoder3Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.incrementPulseWidth();
            } else {
                viewModel.incrementTune();
            }
        }
    }
}

void OscillatorView::encoder3Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.decrementPulseWidth();
            } else {
                viewModel.decrementTune();
            }
        }
    }
}


void OscillatorView::encoder4Increased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.incrementSpread();
            } else {
                viewModel.incrementFineTune();
            }
        }
    }
}

void OscillatorView::encoder4Decreased() {
    if (isShowing()) {
        if (midiCommandManager.getFocusedComponent() == this) {
            if (midiCommandManager.isShiftDown) {
                viewModel.decrementSpread();
            } else {
                viewModel.decrementFineTune();
            }
        }
    }
}

void OscillatorView::shiftButtonPressed() {
    pluginKnobs.showSecondaryKnobs();
}

void OscillatorView::shiftButtonReleased() {
    pluginKnobs.showPrimaryKnobs();
}

void OscillatorView::parametersChanged(){
    pluginKnobs.getKnob(0)->getSlider().setValue(viewModel.getWaveShape(), juce::dontSendNotification);
    pluginKnobs.getKnob(1)->getSlider().setValue(viewModel.getVoices(), juce::dontSendNotification);
    pluginKnobs.getKnob(2)->getSlider().setValue(viewModel.getTune(), juce::dontSendNotification);
    pluginKnobs.getKnob(3)->getSlider().setValue(viewModel.getFineTune(), juce::dontSendNotification);
    pluginKnobs.getKnob(4)->getSlider().setValue(viewModel.getDetune(), juce::dontSendNotification);
    pluginKnobs.getKnob(5)->getSlider().setValue(viewModel.getLevel(), juce::dontSendNotification);
    pluginKnobs.getKnob(6)->getSlider().setValue(viewModel.getPulseWidth(), juce::dontSendNotification);
    pluginKnobs.getKnob(7)->getSlider().setValue(viewModel.getSpread(), juce::dontSendNotification);
}

