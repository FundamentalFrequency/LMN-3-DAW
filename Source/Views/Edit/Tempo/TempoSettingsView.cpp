#include "TempoSettingsView.h"

TempoSettingsView::TempoSettingsView(tracktion_engine::Edit &e,
                                     app_services::MidiCommandManager &mcm)
    : edit(e), viewModel(edit), midiCommandManager(mcm) {
    midiCommandManager.addListener(this);
    viewModel.addListener(this);

    addAndMakeVisible(beatSettingsComponent);

    gainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    gainSlider.setRange(viewModel.clickTrackGainLowerLimit,
                        viewModel.clickTrackGainUpperLimit, .02);
    gainSlider.setColour(juce::Slider::textBoxOutlineColourId,
                         appLookAndFeel.redColour);
    gainSlider.setColour(juce::Slider::backgroundColourId,
                         appLookAndFeel.redColour);
    gainSlider.setColour(juce::Slider::trackColourId, appLookAndFeel.redColour);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(gainSlider);

    gainIcon.setFont(fontAwesomeFont);
    gainIcon.setText(juce::String::charToString(0xf017),
                     juce::dontSendNotification);
    gainIcon.setJustificationType(juce::Justification::centred);
    gainIcon.setAlwaysOnTop(true);
    gainIcon.setColour(juce::Label::textColourId, appLookAndFeel.redColour);
    addAndMakeVisible(gainIcon);

    tapIcon.setFont(fontAwesomeFont);
    tapIcon.setText(juce::String::charToString(0xf0a6),
                    juce::dontSendNotification);
    tapIcon.setJustificationType(juce::Justification::centred);
    tapIcon.setAlwaysOnTop(true);
    tapIcon.setColour(juce::Label::textColourId, appLookAndFeel.textColour);
    addChildComponent(tapIcon);
}

TempoSettingsView::~TempoSettingsView() {
    midiCommandManager.removeListener(this);
    viewModel.removeListener(this);
}

void TempoSettingsView::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void TempoSettingsView::resized() {
    double padding = getHeight() * .08;

    int beatSettingsWidth = getWidth() - 2 * padding;
    int beatSettingsX = (getWidth() / 2) - (beatSettingsWidth / 2);
    beatSettingsComponent.setBounds(beatSettingsX, 2 * padding,
                                    beatSettingsWidth,
                                    getHeight() - 2 * padding);

    fontAwesomeFont.setHeight(getHeight() * .1);
    gainIcon.setFont(fontAwesomeFont);
    gainIcon.setBounds(getWidth() - padding - getHeight() * .21, padding,
                       getHeight() * .21, getHeight() * .2);

    int sliderWidth = 6;
    int gainSliderX =
        gainIcon.getX() + (gainIcon.getWidth() / 2.0) - sliderWidth / 2.0 + 1;
    int gainSliderY = gainIcon.getY() + gainIcon.getHeight();
    gainSlider.setBounds(gainSliderX, gainSliderY, sliderWidth,
                         getHeight() - padding - gainSliderY);

    tapIcon.setFont(fontAwesomeFont);
    tapIcon.setBounds(padding, padding, getHeight() * .11, getHeight() * .1);
}

void TempoSettingsView::encoder1Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementBpm();
}

void TempoSettingsView::encoder1Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementBpm();
}

void TempoSettingsView::encoder4Increased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.incrementClickTrackGain();
}

void TempoSettingsView::encoder4Decreased() {
    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.decrementClickTrackGain();
}

void TempoSettingsView::tempoSettingsButtonPressed() {
    viewModel.enableTapMode();
}

void TempoSettingsView::bpmChanged(const double newBpm, const double newBps) {
    beatSettingsComponent.setBpm(newBpm);
}

void TempoSettingsView::clickTrackGainChanged(const double newGain) {
    gainSlider.setValue(newGain);
    repaint();
}

void TempoSettingsView::tapModeChanged(const bool newTapMode) {
    tapIcon.setVisible(newTapMode);
}
