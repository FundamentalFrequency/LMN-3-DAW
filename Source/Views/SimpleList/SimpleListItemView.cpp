#include "SimpleListItemView.h"

SimpleListItemView::SimpleListItemView(juce::String title)
{

    backgroundColour = juce::Colours::black;
    textColour = juce::Colours::white;

    titleLabel.setFont (juce::Font (getHeight() * .7, juce::Font::bold));
    titleLabel.setText(title, juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    titleLabel.setMinimumHorizontalScale(1.0);
    addAndMakeVisible(titleLabel);

}

void SimpleListItemView::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);
}

void SimpleListItemView::resized()
{

    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7,  juce::Font::plain);
    titleLabel.setFont(font);
    titleLabel.setBounds(0, 0, getWidth(), getHeight());
}

void SimpleListItemView::setTitle(juce::String t)
{
    titleLabel.setText(t, juce::dontSendNotification);
}

void SimpleListItemView::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
    {
        backgroundColour = juce::Colours::white;
        textColour = juce::Colours::black;

    } else {

        backgroundColour = juce::Colours::black;
        textColour = juce::Colours::white;

    }

    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();

}

