#include "MixerTrackView.h"

MixerTrackView::MixerTrackView(tracktion_engine::AudioTrack::Ptr t)
    : track(t),
      viewModel(track),
      levelMeter(std::make_unique<LevelMeterComponent>(track->getLevelMeterPlugin()->measurer))
{

    addAndMakeVisible(levelMeter.get());
    panKnob.getLabel().setText(track->getName().trimCharactersAtStart("Track "), juce::dontSendNotification);
    panKnob.getSlider().setRange(viewModel.getVolumeAndPanPlugin()->panParam->getValueRange().getStart(),
                                 viewModel.getVolumeAndPanPlugin()->panParam->getValueRange().getEnd(), 0);
    panKnob.getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
    panKnob.getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);
    panKnob.getSlider().setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(panKnob);

    volumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    volumeSlider.setRange(0,
                          1, .01);
    volumeSlider.setColour(juce::Slider::textBoxOutlineColourId, appLookAndFeel.redColour);
    volumeSlider.setColour(juce::Slider::backgroundColourId, appLookAndFeel.redColour);
    volumeSlider.setColour(juce::Slider::trackColourId, appLookAndFeel.redColour);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(volumeSlider);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track (Fr (1)) };
    grid.templateColumns = { Track(Fr(5)), Track(Fr(10)), Track(Fr(1)) };

    grid.items.add(levelMeter.get());
    grid.items.add(panKnob);
    grid.items.add(volumeSlider);

    soloLabel.setFont(sharedFontAudio->getFont());
    soloLabel.setText(soloIcon, juce::dontSendNotification );
    soloLabel.setJustificationType(juce::Justification::centred);
    soloLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour3);
    soloLabel.setAlwaysOnTop(true);
    addAndMakeVisible(soloLabel);

    muteLabel.setFont(sharedFontAudio->getFont());
    muteLabel.setText(muteIcon, juce::dontSendNotification );
    muteLabel.setJustificationType(juce::Justification::centred);
    muteLabel.setColour(juce::Label::textColourId, appLookAndFeel.colour4);
    muteLabel.setAlwaysOnTop(true);
    addAndMakeVisible(muteLabel);

    viewModel.addListener(this);

}

MixerTrackView::~MixerTrackView()
{

    viewModel.removeListener(this);

}

void MixerTrackView::paint(juce::Graphics& g)
{

    if (isSelected)
    {

        g.setColour(appLookAndFeel.colour1);
        g.drawRect(getLocalBounds(), 2);
    }

}

void MixerTrackView::resized()
{

    grid.performLayout(getLocalBounds().reduced(getWidth() * .05));


    int iconHeight = getHeight() / 4;
    int iconWidth = iconHeight;
    int soloX = (panKnob.getX() + (panKnob.getWidth() / 2)) - iconWidth - 10;
    int muteX = (panKnob.getX() + (panKnob.getWidth() / 2)) + 10 + 2;
    int iconY = panKnob.getLabel().getY() + 5;

    soloLabel.setFont(sharedFontAudio->getFont(iconHeight * .6));
    muteLabel.setFont(sharedFontAudio->getFont(iconHeight * .6));
    soloLabel.setBounds(soloX, iconY, iconWidth, iconHeight);
    muteLabel.setBounds(muteX, iconY, iconWidth, iconHeight);

}

void MixerTrackView::setSelected(bool selected)
{

    isSelected = selected;
    if (isSelected)
        panKnob.getLabel().setColour(juce::Label::textColourId, appLookAndFeel.colour1);
    else
        panKnob.getLabel().setColour(juce::Label::textColourId, appLookAndFeel.colour3);

}

void MixerTrackView::panChanged(double pan)
{

    panKnob.getSlider().setValue(pan, juce::dontSendNotification);

}

void MixerTrackView::volumeChanged(double volume)
{

    volumeSlider.setValue(volume, juce::dontSendNotification);

}

void MixerTrackView::soloStateChanged(bool solo)
{

    soloLabel.setVisible(solo);
    resized();

}

void MixerTrackView::muteStateChanged(bool mute)
{

    muteLabel.setVisible(mute);
    resized();

}
