#include "LoopMarkerComponent.h"

void LoopMarkerComponent::paint(juce::Graphics &g) {
    g.setColour(appLookAndFeel.colour2);

    g.drawLine(getHeight(), getHeight() / 2, getWidth() - getHeight(),
               getHeight() / 2, 8);
    g.fillEllipse(0, 0, getHeight(), getHeight());
    g.fillEllipse(getWidth() - getHeight(), 0, getHeight(), getHeight());

    // inner circle to differentiate start from end
    g.setColour(appLookAndFeel.backgroundColour);
    int outerRadius = getHeight() / 2;
    int innerRadius = outerRadius * .8;
    int diff = outerRadius - innerRadius;
    int outerStart = getWidth() - getHeight();
    g.fillEllipse(outerStart + diff, diff, 2 * innerRadius, 2 * innerRadius);
}
