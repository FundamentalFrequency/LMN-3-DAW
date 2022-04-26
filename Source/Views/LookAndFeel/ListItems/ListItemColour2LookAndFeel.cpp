#include "ListItemColour2LookAndFeel.h"
#include "SimpleListItemView.h"

ListItemColour2LookAndFeel::ListItemColour2LookAndFeel() {
    setColour(SimpleListItemView::unselectedBackgroundColourId,
              backgroundColour);
    setColour(SimpleListItemView::selectedBackgroundColourId, colour2);
    setColour(SimpleListItemView::unselectedTextColourId, colour2);
    setColour(SimpleListItemView::selectedTextColourId, backgroundColour);

    setColour(juce::ScrollBar::thumbColourId, colour2);
}
