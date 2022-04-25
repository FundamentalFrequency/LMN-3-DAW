#include "ListTitle.h"

ListTitle::ListTitle(const juce::String& titleString, IconType type, const juce::String& iconString)
    : title(titleString),
      iconType(type),
      icon(iconString)
{


    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText(title, juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    titleLabel.setAlwaysOnTop(true);
    titleLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(titleLabel);

    switch (iconType)
    {
        case IconType::FONT_AWESOME:
            iconLabel.setFont(fontAwesomeFont);
            break;

        default:
            iconLabel.setFont(fontAwesomeFont);
            break;

    }

    iconLabel.setText(icon, juce::dontSendNotification );
    iconLabel.setJustificationType(juce::Justification::right);
    iconLabel.setAlwaysOnTop(true);
    iconLabel.setLookAndFeel(&labelColour1LookAndFeel);
    addAndMakeVisible(iconLabel);

}

ListTitle::~ListTitle()
{

    titleLabel.setLookAndFeel(nullptr);
    iconLabel.setLookAndFeel(nullptr);

}

void ListTitle::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

void ListTitle::resized()
{

    titleLabel.setBounds(0, 0, getWidth() * .9, getHeight());
    iconLabel.setBounds(getWidth() * .9, 0, getWidth() * .1, getHeight());

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7, juce::Font::plain));

    switch (iconType)
    {
        case IconType::FONT_AWESOME:
            fontAwesomeFont.setHeight(getHeight() * .75 * .8);
            iconLabel.setFont(fontAwesomeFont);
            break;

        default:
            fontAwesomeFont.setHeight(getHeight() * .75 * .8);
            iconLabel.setFont(fontAwesomeFont);
            break;

    }

}