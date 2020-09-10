#include "AppLookAndFeel.h"
#include "TrackView.h"
#include "SimpleListItemView.h"

AppLookAndFeel::AppLookAndFeel()
{

    setColour(juce::DocumentWindow::backgroundColourId, backgroundColour);

    setColour(juce::TabbedComponent::backgroundColourId, backgroundColour);

    setColour(juce::Label::textColourId, textColour);

    setColour(juce::ListBox::backgroundColourId, backgroundColour);

    setColour(SimpleListItemView::unselectedBackgroundColourId, backgroundColour);
    setColour(SimpleListItemView::selectedBackgroundColourId, colour1);
    setColour(SimpleListItemView::unselectedTextColourId, colour1);
    setColour(SimpleListItemView::selectedTextColourId, backgroundColour);

    setColour(juce::ScrollBar::thumbColourId, colour1);
    setColour(juce::ScrollBar::trackColourId, colour2);


}