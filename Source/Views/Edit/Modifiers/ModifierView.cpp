#include "ModifierView.h"
#include <app_navigation/app_navigation.h>

ModifierView::ModifierView(tracktion::Modifier *mod,
                           app_services::MidiCommandManager &mcm)
    : viewModel(std::make_unique<app_view_models::ModifierViewModel>(mod)),
      midiCommandManager(mcm), knobs(mcm, 8) {
    init();
}

ModifierView::ModifierView(tracktion::LFOModifier *mod,
                           app_services::MidiCommandManager &mcm)
    : viewModel(std::unique_ptr<app_view_models::ModifierViewModel>(
          std::make_unique<app_view_models::LFOModifierViewModel>(mod))),
      midiCommandManager(mcm), knobs(mcm, 5) {
    init();
}

void ModifierView::init() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setText(viewModel->getModifierName(),
                       juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        knobs.getKnob(i)->getLabel().setText(viewModel->getParameterName(i),
                                             juce::dontSendNotification);
        knobs.getKnob(i)->getSlider().setRange(
            viewModel->getParameterRange(i),
            viewModel->getParameterInterval(i));
    }

    addAndMakeVisible(knobs);

    midiCommandManager.addListener(this);
    viewModel->addListener(this);
}

ModifierView::~ModifierView() {
    midiCommandManager.removeListener(this);
    viewModel->removeListener(this);
}

void ModifierView::paint(juce::Graphics &g) {}

void ModifierView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                  getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

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

void ModifierView::controlButtonPressed() {
    if (viewModel->getNumberOfParameters() > 4) {
        for (int i = 0; i < 8; i++) {
            if (i < 4)
                knobs.getKnob(i)->setVisible(false);
            else
                knobs.getKnob(i)->setVisible(true);
        }
    }
}

void ModifierView::controlButtonReleased() {
    if (viewModel->getNumberOfParameters() > 4) {
        for (int i = 0; i < 8; i++) {
            if (i < 4)
                knobs.getKnob(i)->setVisible(true);
            else
                knobs.getKnob(i)->setVisible(false);
        }
    }
}

void ModifierView::encoder1Increased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) +
                                            viewModel->getParameterInterval(0));
    else
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) +
                                            viewModel->getParameterInterval(4));
}

void ModifierView::encoder1Decreased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) -
                                            viewModel->getParameterInterval(0));
    else
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) -
                                            viewModel->getParameterInterval(4));
}

void ModifierView::encoder2Increased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) +
                                            viewModel->getParameterInterval(1));
    else
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) +
                                            viewModel->getParameterInterval(5));
}

void ModifierView::encoder2Decreased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) -
                                            viewModel->getParameterInterval(1));
    else
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) -
                                            viewModel->getParameterInterval(5));
}

void ModifierView::encoder3Increased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) +
                                            viewModel->getParameterInterval(2));
    else
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) +
                                            viewModel->getParameterInterval(6));
}

void ModifierView::encoder3Decreased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) -
                                            viewModel->getParameterInterval(2));
    else
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) -
                                            viewModel->getParameterInterval(6));
}

void ModifierView::encoder4Increased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) +
                                            viewModel->getParameterInterval(3));
    else
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) +
                                            viewModel->getParameterInterval(7));
}

void ModifierView::encoder4Decreased() {
    if (!midiCommandManager.isControlDown)
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) -
                                            viewModel->getParameterInterval(3));
    else
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) -
                                            viewModel->getParameterInterval(7));
}

void ModifierView::parametersChanged() {
    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        knobs.getKnob(i)->getSlider().setValue(viewModel->getParameterValue(i),
                                               juce::dontSendNotification);
    }
}
