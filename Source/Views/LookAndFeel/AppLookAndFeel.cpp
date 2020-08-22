#include "AppLookAndFeel.h"
#include "TrackView.h"
#include "SimpleListItemView.h"

AppLookAndFeel::AppLookAndFeel()
{

    setColour(juce::DocumentWindow::backgroundColourId, backgroundColour);

    setColour(juce::TabbedComponent::backgroundColourId, backgroundColour);

    setColour(juce::Label::textColourId, textColour);

    setColour(juce::ListBox::backgroundColourId, backgroundColour);

    setColour(TrackView::unselectedBackgroundColourId, backgroundColour);
    setColour(TrackView::selectedBackgroundColourId, colour1);
    setColour(TrackView::unselectedTextColourId, colour1);
    setColour(TrackView::selectedTextColourId, colour1);

    setColour(SimpleListItemView::unselectedBackgroundColourId, backgroundColour);
    setColour(SimpleListItemView::selectedBackgroundColourId, colour1);
    setColour(SimpleListItemView::unselectedTextColourId, colour1);
    setColour(SimpleListItemView::selectedTextColourId, textColour);

    setColour(juce::ScrollBar::thumbColourId, colour1);

}