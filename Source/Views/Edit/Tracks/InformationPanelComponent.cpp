#include "InformationPanelComponent.h"
#include "LabelColour1LookAndFeel.h"

InformationPanelComponent::InformationPanelComponent() {
    trackNumberLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7,
                   juce::Font::plain));
    trackNumberLabel.setText("1", juce::dontSendNotification);
    trackNumberLabel.setJustificationType(juce::Justification::centred);
    trackNumberLabel.setAlwaysOnTop(true);
    trackNumberLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(trackNumberLabel);

    timecodeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                     getHeight() * .7, juce::Font::plain));
    timecodeLabel.setText("time", juce::dontSendNotification);
    timecodeLabel.setJustificationType(juce::Justification::centred);
    timecodeLabel.setAlwaysOnTop(true);
    addAndMakeVisible(timecodeLabel);

    loopingLabel.setFont(fontAwesomeFont);
    loopingLabel.setText(juce::String::charToString(0xf363),
                         juce::dontSendNotification);
    loopingLabel.setJustificationType(juce::Justification::centred);
    loopingLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour2);
    loopingLabel.setAlwaysOnTop(true);
    addAndMakeVisible(loopingLabel);

    soloLabel.setFont(fontAwesomeFont);
    soloLabel.setText(juce::String::charToString(0x53),
                      juce::dontSendNotification);
    soloLabel.setJustificationType(juce::Justification::centred);
    soloLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour3);
    soloLabel.setAlwaysOnTop(true);
    addAndMakeVisible(soloLabel);

    muteLabel.setFont(fontAwesomeFont);
    muteLabel.setText(juce::String::charToString(0xf6a9),
                      juce::dontSendNotification);
    muteLabel.setJustificationType(juce::Justification::centred);
    muteLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour4);
    muteLabel.setAlwaysOnTop(true);
    addAndMakeVisible(muteLabel);
}

InformationPanelComponent::~InformationPanelComponent() {
    trackNumberLabel.setLookAndFeel(nullptr);
}

void InformationPanelComponent::paint(juce::Graphics &) {}

void InformationPanelComponent::resized() {
    double height = getHeight() * .5;
    // font awesome needs to be scaled down just a bit more
    fontAwesomeFont.setHeight(height * .6);

    loopingLabel.setFont(fontAwesomeFont);
    soloLabel.setFont(fontAwesomeFont);
    muteLabel.setFont(fontAwesomeFont);
    float iconHeight = float(height);

    trackNumberLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), iconHeight,
                   juce::Font::plain));
    int trackNumberLabelX = 5;
    trackNumberLabel.setBounds(
        trackNumberLabelX, 0,
        trackNumberLabel.getFont().getStringWidthFloat("10") + 10, getHeight());

    timecodeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                     iconHeight, juce::Font::plain));
    int timeCodeLabelX =
        .5 * getWidth() - (.5 * timecodeLabel.getFont().getStringWidthFloat(
                                    timecodeLabel.getText()));
    timecodeLabel.setBounds(
        timeCodeLabelX, 0,
        timecodeLabel.getFont().getStringWidthFloat(timecodeLabel.getText()),
        getHeight());

    int loopLabelX = getWidth() - 2 * height;
    loopingLabel.setBounds(loopLabelX, 0, getHeight(), getHeight());
    // recordingLabel.setBounds(playingStatusLabelX, 0, getHeight(),
    // getHeight());

    int soloLabelX = trackNumberLabelX + trackNumberLabel.getWidth() + 5;
    soloLabel.setBounds(soloLabelX, 0, getHeight(), getHeight());

    int muteLabelX = soloLabelX + 60;
    muteLabel.setBounds(muteLabelX, 0, getHeight(), getHeight());
}

void InformationPanelComponent::setIsPlaying(bool isPlaying) { resized(); }

void InformationPanelComponent::setIsRecording(bool isRecording) {
    if (isRecording) {
        timecodeLabel.setColour(juce::Label::textColourId,
                                appLookAndFeel.redColour);

    } else {
        timecodeLabel.setColour(juce::Label::textColourId,
                                appLookAndFeel.textColour);
    }

    resized();
}

void InformationPanelComponent::setTimecode(juce::String timecode) {
    timecodeLabel.setText(timecode, juce::dontSendNotification);
    resized();
}

void InformationPanelComponent::setTrackNumber(juce::String trackNumber) {
    trackNumberLabel.setText(trackNumber, juce::dontSendNotification);
    resized();
}

void InformationPanelComponent::setIsLooping(bool isLooping) {
    loopingLabel.setVisible(isLooping);
    resized();
}

void InformationPanelComponent::setIsSoloed(bool solo) {
    soloLabel.setVisible(solo);
    resized();
}

void InformationPanelComponent::setIsMuted(bool muted) {
    muteLabel.setVisible(muted);
    resized();
}