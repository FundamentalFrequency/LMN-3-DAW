#include "OscillatorView.h"

OscillatorView::OscillatorView(tracktion_engine::FourOscPlugin* p, int oscIndex, app_services::MidiCommandManager& mcm)
: viewModel(p, oscIndex),
  midiCommandManager(mcm) {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText("4OSC: OSC " + juce::String(oscIndex + 1), juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

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

    for (int i = 0; i < 8; i++) {
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
    knobs[0]->getLabel().setText("Wave Shape", juce::dontSendNotification);
    knobs[0]->getSlider().setRange(0, 6, 1);

    knobs[1]->getLabel().setText("Voices", juce::dontSendNotification);
    knobs[1]->getSlider().setRange(1, 8, 1);

    knobs[2]->getLabel().setText("Tune", juce::dontSendNotification);
    knobs[2]->getSlider().setRange(0, 1, 0);
    knobs[2]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[3]->getLabel().setText("Fine Tune", juce::dontSendNotification);
    knobs[3]->getSlider().setRange(0, 1, 0);
    knobs[3]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[4]->getLabel().setText("Detune", juce::dontSendNotification);
    knobs[4]->getSlider().setRange(0, 1, 0);
    knobs[4]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[5]->getLabel().setText("Level", juce::dontSendNotification);
    knobs[5]->getSlider().setRange(0, 1, 0);
    knobs[5]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[6]->getLabel().setText("Pulse Width", juce::dontSendNotification);
    knobs[6]->getSlider().setRange(0, 1, 0);
    knobs[6]->getSlider().setNumDecimalPlacesToDisplay(2);

    knobs[7]->getLabel().setText("Spread", juce::dontSendNotification);
    knobs[7]->getSlider().setRange(0, 1, 0);
    knobs[7]->getSlider().setNumDecimalPlacesToDisplay(2);

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
    gridSetup();
}

void OscillatorView::gridSetup() {
    int knobWidth = getWidth() / 8;
    int knobHeight = getHeight() / 3;
    int knobSpacing = knobWidth;

    grid1.setGap(juce::Grid::Px(knobSpacing));
    grid2.setGap(juce::Grid::Px(knobSpacing));

    int width = (4 * knobWidth) + (3 * knobSpacing);
    int height = knobHeight;
    int startX = (getWidth() / 2) - (width / 2);
    int startY = (getHeight() / 2) - (knobHeight / 2);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid1.performLayout(bounds);
    grid2.performLayout(bounds);
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
    for (int i = 0; i < knobs.size(); i++) {
        if (i < knobs.size() / 2) {
            knobs[i]->setVisible(false);
        } else {
            knobs[i]->setVisible(true);
        }
    }
}

void OscillatorView::shiftButtonReleased() {
    for (int i = 0; i < knobs.size(); i++) {
        if (i < knobs.size() / 2) {
            knobs[i]->setVisible(true);
        } else {
            knobs[i]->setVisible(false);
        }
    }
}

void OscillatorView::parametersChanged(){
    knobs[0]->getSlider().setValue(viewModel.getWaveShape(), juce::dontSendNotification);
    knobs[1]->getSlider().setValue(viewModel.getVoices(), juce::dontSendNotification);
    knobs[2]->getSlider().setValue(viewModel.getTune(), juce::dontSendNotification);
    knobs[3]->getSlider().setValue(viewModel.getFineTune(), juce::dontSendNotification);
    knobs[4]->getSlider().setValue(viewModel.getDetune(), juce::dontSendNotification);
    knobs[5]->getSlider().setValue(viewModel.getLevel(), juce::dontSendNotification);
    knobs[6]->getSlider().setValue(viewModel.getPulseWidth(), juce::dontSendNotification);
    knobs[7]->getSlider().setValue(viewModel.getSpread(), juce::dontSendNotification);
}

