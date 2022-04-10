#include "InternalPluginView.h"
#include <app_navigation/app_navigation.h>

InternalPluginView::InternalPluginView(tracktion_engine::Plugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::make_unique<app_view_models::InternalPluginViewModel>(p)),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::ReverbPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::ReverbPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::DelayPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::DelayPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::PhaserPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::PhaserPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()){
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::ChorusPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::ChorusPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::EqualiserPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::EqualiserPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

InternalPluginView::InternalPluginView(tracktion_engine::CompressorPlugin* p, app_services::MidiCommandManager& mcm)
: viewModel(std::unique_ptr<app_view_models::InternalPluginViewModel>(std::make_unique<app_view_models::CompressorPluginViewModel>(p))),
  midiCommandManager(mcm),
  pluginKnobs(viewModel->getNumberOfParameters()) {
    init();
}

void InternalPluginView::init() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText(viewModel->getPluginName(), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        pluginKnobs.getKnob(i)->getLabel().setText(viewModel->getParameterName(i), juce::dontSendNotification);
        pluginKnobs.getKnob(i)->getSlider().setRange(viewModel->getParameterRange(i), viewModel->getParameterInterval(i));
    }

    addAndMakeVisible(pluginKnobs);

    midiCommandManager.addListener(this);
    viewModel->addListener(this);
}


InternalPluginView::~InternalPluginView() {
    midiCommandManager.removeListener(this);
    viewModel->removeListener(this);
}

void InternalPluginView::resized() {
    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

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


void InternalPluginView::shiftButtonPressed() {
    pluginKnobs.showSecondaryKnobs();
}

void InternalPluginView::shiftButtonReleased() {
    pluginKnobs.showPrimaryKnobs();
}

void InternalPluginView::encoder1Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) + viewModel->getParameterInterval(0));
    } else {
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) + viewModel->getParameterInterval(4));
    }
}

void InternalPluginView::encoder1Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) - viewModel->getParameterInterval(0));
    } else {
        viewModel->setParameterValue(4, viewModel->getParameterValue(4) - viewModel->getParameterInterval(4));
    }
}

void InternalPluginView::encoder2Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) + viewModel->getParameterInterval(1));
    } else {
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) + viewModel->getParameterInterval(5));
    }
}

void InternalPluginView::encoder2Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) - viewModel->getParameterInterval(1));
    } else {
        viewModel->setParameterValue(5, viewModel->getParameterValue(5) - viewModel->getParameterInterval(5));
    }
}

void InternalPluginView::encoder3Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) + viewModel->getParameterInterval(2));
    } else {
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) + viewModel->getParameterInterval(6));
    }
}

void InternalPluginView::encoder3Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) - viewModel->getParameterInterval(2));
    } else {
        viewModel->setParameterValue(6, viewModel->getParameterValue(6) - viewModel->getParameterInterval(6));
    }
}

void InternalPluginView::encoder4Increased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) + viewModel->getParameterInterval(3));
    } else {
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) + viewModel->getParameterInterval(7));
    }
}

void InternalPluginView::encoder4Decreased() {
    if (!midiCommandManager.isShiftDown) {
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) - viewModel->getParameterInterval(3));
    } else {
        viewModel->setParameterValue(7, viewModel->getParameterValue(7) - viewModel->getParameterInterval(7));
    }
}

void InternalPluginView::parametersChanged() {
    for (int i = 0; i < viewModel->getNumberOfParameters(); i++) {
        pluginKnobs.setKnobValue(i, viewModel->getParameterValue(i));
    }
}
