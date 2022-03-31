#include "ProgressView.h"

ProgressView::ProgressView()
{

}

void ProgressView::paint(juce::Graphics& g)
{
    g.setColour(appLookAndFeel.whiteColour);
    g.drawRect(getBounds());
}

void ProgressView::resized()
{

}

