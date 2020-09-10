#include "InformationPanelComponent.h"
#include "LabelColour1LookAndFeel.h"

InformationPanelComponent::InformationPanelComponent()
{

//    playingLabel.setFont(fontAwesomeFont);
//    playingLabel.setText(playIcon, juce::dontSendNotification );
//    playingLabel.setJustificationType(juce::Justification::centred);
//    playingLabel.setMinimumHorizontalScale(1.0);
//    playingLabel.setAlwaysOnTop(true);
//    addAndMakeVisible(playingLabel);
//
//    recordingLabel.setFont(sharedFontAudio->getFont());
//    recordingLabel.setText(recordIcon, juce::dontSendNotification );
//    recordingLabel.setJustificationType(juce::Justification::centred);
//    //recordingLabel.setMinimumHorizontalScale(1.0);
//    recordingLabel.setColour(juce::Label::textColourId, juce::Colours::red);
//    recordingLabel.setAlwaysOnTop(true);
//    addAndMakeVisible(recordingLabel);

    trackNumberLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7, juce::Font::plain));
    trackNumberLabel.setText("1", juce::dontSendNotification );
    trackNumberLabel.setJustificationType(juce::Justification::centred);
    trackNumberLabel.setAlwaysOnTop(true);
    trackNumberLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(trackNumberLabel);

    timecodeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7, juce::Font::plain));
    timecodeLabel.setText("time", juce::dontSendNotification );
    timecodeLabel.setJustificationType(juce::Justification::centred);
    timecodeLabel.setAlwaysOnTop(true);
    addAndMakeVisible(timecodeLabel);


}

InformationPanelComponent::~InformationPanelComponent()
{

    trackNumberLabel.setLookAndFeel(nullptr);
}

void InformationPanelComponent::paint(juce::Graphics&)
{

}

void InformationPanelComponent::resized()
{

    double height = getHeight() * .5;
    // font awesome needs to be scaled down just a bit more
    fontAwesomeFont.setHeight(height * .6);
    playingLabel.setFont(fontAwesomeFont);
    recordingLabel.setFont(sharedFontAudio->getFont(height));
    float iconHeight = float(height);



    trackNumberLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), iconHeight, juce::Font::plain));
    int trackNumberLabelX = 5;
    trackNumberLabel.setBounds(trackNumberLabelX, 0, trackNumberLabel.getFont().getStringWidthFloat("10") + 10, getHeight());

    timecodeLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), iconHeight, juce::Font::plain));
    int timeCodeLabelX = .5 * getWidth() - (.5 * timecodeLabel.getFont().getStringWidthFloat(timecodeLabel.getText()));
    timecodeLabel.setBounds(timeCodeLabelX, 0, timecodeLabel.getFont().getStringWidthFloat(timecodeLabel.getText()), getHeight());

    int playingStatusLabelX = timeCodeLabelX + timecodeLabel.getWidth() - getHeight()*.5 + 4;
    playingLabel.setBounds(playingStatusLabelX, 0, getHeight(), getHeight());
    recordingLabel.setBounds(playingStatusLabelX, 0, getHeight(), getHeight());

}

void InformationPanelComponent::setIsPlaying(bool isPlaying)
{

    if (isPlaying)
        playingLabel.setVisible(true);
    else
        playingLabel.setVisible(false);

    resized();
}

void InformationPanelComponent::setIsRecording(bool isRecording)
{

    if (isRecording)
    {

        recordingLabel.setVisible(true);
        timecodeLabel.setColour(juce::Label::textColourId, appLookAndFeel.redColour);

    }
    else
    {

        recordingLabel.setVisible(false);
        timecodeLabel.setColour(juce::Label::textColourId, appLookAndFeel.textColour);

    }

    resized();

}

void InformationPanelComponent::setTimecode(juce::String timecode)
{

    timecodeLabel.setText(timecode, juce::dontSendNotification);
    resized();

}

void InformationPanelComponent::setTrackNumber(juce::String trackNumber)
{

    trackNumberLabel.setText(trackNumber, juce::dontSendNotification);
    resized();
}