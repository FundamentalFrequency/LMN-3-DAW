#include "BeatSettingsComponent.h"

BeatSettingsComponent::BeatSettingsComponent() {

    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                getHeight() * .3, juce::Font::plain));
    bpmLabel.setText("BPM", juce::dontSendNotification);
    bpmLabel.setJustificationType(juce::Justification::centred);
    bpmLabel.setAlwaysOnTop(true);
    bpmLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(bpmLabel);

    currentBpmValueLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .3,
                   juce::Font::plain));
    currentBpmValueLabel.setText("120", juce::dontSendNotification);
    currentBpmValueLabel.setJustificationType(juce::Justification::centred);
    currentBpmValueLabel.setAlwaysOnTop(true);
    currentBpmValueLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(currentBpmValueLabel);
}

BeatSettingsComponent::~BeatSettingsComponent() {

    bpmLabel.setLookAndFeel(nullptr);
    currentBpmValueLabel.setLookAndFeel(nullptr);
}

void BeatSettingsComponent::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void BeatSettingsComponent::resized() {

    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                getHeight() * .2, juce::Font::plain));
    bpmLabel.setBounds(0, 0, getWidth(), getHeight() * .2);

    currentBpmValueLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .5,
                   juce::Font::plain));
    currentBpmValueLabel.setBounds(0, bpmLabel.getHeight(), getWidth(),
                                   getHeight() * .5);
}

void BeatSettingsComponent::setBpm(double bpm) {
    currentBpmValueLabel.setText(juce::String(bpm), juce::dontSendNotification);
    currentBpmValueLabel.repaint();
}
