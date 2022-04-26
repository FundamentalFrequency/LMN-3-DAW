#include "SelectedTrackMarker.h"

void SelectedTrackMarker::paint(juce::Graphics &g) {
    g.setColour(appLookAndFeel.colour1);
    g.drawRect(getLocalBounds(), 3);
};
