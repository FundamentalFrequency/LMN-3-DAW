#include "InstrumentListRow.h"

InstrumentListRow::InstrumentListRow(juce::String title)
{

    // set default colors
    getLookAndFeel().setColour(selectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedTextColourId, juce::Colours::white);
    getLookAndFeel().setColour(selectedTextColourId, juce::Colours::white);
    backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
    textColour = getLookAndFeel().findColour(unselectedTextColourId);

    titleLabel.setText(title, juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(titleLabel);

}

void InstrumentListRow::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);
}

void InstrumentListRow::resized()
{

    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7,  juce::Font::plain);
    titleLabel.setFont(font);
    titleLabel.setBounds(0, 0, getWidth(), getHeight());
}

void InstrumentListRow::setTitle(juce::String t)
{
    titleLabel.setText(t, juce::dontSendNotification);
}

void InstrumentListRow::setSelected(bool selected)
{
    if (selected)
    {
        backgroundColour = getLookAndFeel().findColour(selectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(selectedTextColourId);

    } else {

        backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(unselectedTextColourId);

    }

    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();
}