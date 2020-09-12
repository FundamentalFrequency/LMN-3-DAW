#include "BeatSettingsComponent.h"


BeatSettingsComponent::BeatSettingsComponent()
{

    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .3, juce::Font::plain));
    bpmLabel.setText("BPM", juce::dontSendNotification );
    bpmLabel.setJustificationType(juce::Justification::centred);
    bpmLabel.setAlwaysOnTop(true);
    bpmLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(bpmLabel);

    currentBpmValueLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .3, juce::Font::plain));
    currentBpmValueLabel.setText("120", juce::dontSendNotification );
    currentBpmValueLabel.setJustificationType(juce::Justification::centred);
    currentBpmValueLabel.setAlwaysOnTop(true);
    currentBpmValueLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(currentBpmValueLabel);

    bpsLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .3, juce::Font::plain));
    bpsLabel.setText("BPS", juce::dontSendNotification );
    bpsLabel.setJustificationType(juce::Justification::centred);
    bpsLabel.setAlwaysOnTop(true);
    bpsLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(bpsLabel);

    currentBpsValueLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .3, juce::Font::plain));
    currentBpsValueLabel.setText("2", juce::dontSendNotification );
    currentBpsValueLabel.setJustificationType(juce::Justification::centred);
    currentBpsValueLabel.setAlwaysOnTop(true);
    currentBpsValueLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(currentBpsValueLabel);


}

BeatSettingsComponent::~BeatSettingsComponent()
{

    bpmLabel.setLookAndFeel(nullptr);
    currentBpmValueLabel.setLookAndFeel(nullptr);

    bpsLabel.setLookAndFeel(nullptr);
    currentBpsValueLabel.setLookAndFeel(nullptr);

}

void BeatSettingsComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void BeatSettingsComponent::resized()
{

    int padding = getWidth() * .05;


    bpmLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .2, juce::Font::plain));
    bpmLabel.setBounds(0, 0, getWidth() * .5 - padding/2, getHeight() * .2);

    currentBpmValueLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .5, juce::Font::plain));
    currentBpmValueLabel.setBounds(0, bpmLabel.getHeight() + padding, getWidth() * .5 - padding/2, getHeight() * .5);

    bpsLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .2, juce::Font::plain));
    bpsLabel.setBounds(getWidth() * .5 + padding/2, 0, getWidth() * .5 - padding/2, getHeight() * .2);

    currentBpsValueLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .5, juce::Font::plain));
    currentBpsValueLabel.setBounds(getWidth() * .5 + padding/2, bpsLabel.getHeight() + padding, getWidth() * .5 - padding/2, getHeight() * .5);


}

void BeatSettingsComponent::setBpm(double bpm)
{

    currentBpmValueLabel.setText(juce::String(bpm), juce::dontSendNotification);
    currentBpmValueLabel.repaint();

}

void BeatSettingsComponent::setBps(double bps)
{

    if (bps >= 1)
        currentBpsValueLabel.setText(juce::String(bps, 2), juce::dontSendNotification);
    else
        currentBpsValueLabel.setText(juce::String(bps, 2), juce::dontSendNotification);
    currentBpsValueLabel.repaint();

}