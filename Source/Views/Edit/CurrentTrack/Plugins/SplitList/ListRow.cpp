#include "ListRow.h"


ListRow::ListRow(const juce::String& title)
    : selectedBackgroundColour(juce::Colours::black)

{

    titleLabel.setText(title, juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(titleLabel);

}

void ListRow::paint(juce::Graphics& g)
{
    if (isSelected)
    {
        g.fillAll(selectedBackgroundColour);
        titleLabel.setColour(juce::Label::textColourId, getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    } else {

        g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        titleLabel.setColour(juce::Label::textColourId, selectedBackgroundColour);

    }

}

void ListRow::resized()
{

    juce::Font font(juce::Font::getDefaultMonospacedFontName(), float(getHeight()) * .7f,  juce::Font::plain);
    titleLabel.setFont(font);
    titleLabel.setBounds(0, 0, getWidth(), getHeight());
}

void ListRow::setTitle(const juce::String& t)
{
    titleLabel.setText(t, juce::dontSendNotification);
}

void ListRow::setSelected(bool selected)
{

    isSelected = selected;
    repaint();

}

void ListRow::setSelectedBackgroundColour(juce::Colour selectedBackgroundColour_)
{

    selectedBackgroundColour = selectedBackgroundColour_;
    repaint();

}