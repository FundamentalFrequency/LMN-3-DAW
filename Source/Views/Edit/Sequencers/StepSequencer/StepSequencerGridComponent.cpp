#include "StepSequencerGridComponent.h"


void StepSequencerGridComponent::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.colour3);

    // Draw bounding rectangle
    g.drawLine(0, 0, getWidth(), 0, 2);
    g.drawLine(getWidth(), 0, getWidth(), getHeight(), 2);
    g.drawLine(getWidth(), getHeight(), 0, getHeight(), 2);
    g.drawLine(0, getHeight(), 0, 0, 2);

    // draw lines for rows
    float rowSpacing = getHeight() / numRows;
    int rowY = rowSpacing;
    for (int i = 0; i < numRows - 1; i++)
    {

        g.drawLine(0, rowY, getWidth(), rowY, 1);
        rowY += rowSpacing;

    }

}

void StepSequencerGridComponent::resized()
{

}


void StepSequencerGridComponent::setNumRows(int rows)
{

    numRows = rows;

}

void StepSequencerGridComponent::setNumColumns(int cols)
{

    numColumns = cols;

}