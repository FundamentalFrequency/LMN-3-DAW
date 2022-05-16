#include "ControlButtonIndicator.h"

ControlButtonIndicator::ControlButtonIndicator(
    app_services::MidiCommandManager &mcm)
    : midiCommandManager(mcm) {
    setLookAndFeel(&appLookAndFeel);
    iconLabel.setText(juce::String::charToString(0xf094),
                      juce::dontSendNotification);
    iconLabel.setColour(juce::Label::textColourId, appLookAndFeel.whiteColour);
    addAndMakeVisible(iconLabel);

    midiCommandManager.addListener(this);
}

ControlButtonIndicator::~ControlButtonIndicator() {
    midiCommandManager.removeListener(this);
    setLookAndFeel(nullptr);
}

void ControlButtonIndicator::paint(juce::Graphics &g) {
    g.fillAll(appLookAndFeel.backgroundColour);
}

void ControlButtonIndicator::resized() {
    //    iconLabel.setBounds(getLocalBounds().reduced(20));
    //    fontAwesomeFont.setHeight(iconLabel.getHeight() * .8);
    iconLabel.setBounds(getLocalBounds());
    fontAwesomeFont.setHeight(iconLabel.getWidth());
    iconLabel.setFont(fontAwesomeFont);
}

void ControlButtonIndicator::controlButtonPressed() {
    iconLabel.setColour(juce::Label::textColourId, appLookAndFeel.yellowColour);
}

void ControlButtonIndicator::controlButtonReleased() {
    iconLabel.setColour(juce::Label::textColourId, appLookAndFeel.whiteColour);
}
