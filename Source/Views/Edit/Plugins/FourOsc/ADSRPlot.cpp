#include "ADSRPlot.h"

void ADSRPlot::paint(juce::Graphics& g)
{

    int paddingTop = 4;
    int paddingBottom = 4;
    int paddingLeft = 4;
    int paddingRight = 4;

//    // draw lines for rows and cols
//    // have to make sure it divides evenly, increase padding a bit until it does
//    int numCols = 20;
//    while((getWidth() - (paddingLeft + paddingRight)) % numCols != 0)
//        paddingLeft += 1;
//    float colSpacing = (getWidth() - (paddingLeft + paddingRight)) / float(numCols);
//
//    float rowSpacing = colSpacing;
//    int numRows = ceil(getHeight() / rowSpacing);
//    while((getHeight() - (paddingBottom + paddingTop)) % numRows != 0)
//        paddingTop += 1;
//
//    g.setColour(appLookAndFeel.whiteColour);
//    g.drawRect(paddingLeft, paddingTop, getWidth() - (paddingLeft + paddingRight), getHeight() - (paddingTop + paddingBottom), 2);
//
//    for (int i = 0; i < numCols; i++)
//        g.drawLine(paddingLeft + (i * colSpacing), paddingTop, paddingLeft + (i * colSpacing), getHeight() - paddingBottom, 2);
//
//    for (int i = 0; i < numRows - 1; i++)
//        g.drawLine(paddingLeft, paddingTop + (i * rowSpacing), getWidth() - paddingRight, paddingTop + (i*rowSpacing), 2);

    // draw lines for rows and cols
    // have to make sure it divides evenly, increase padding a bit until it does
    int numRows = 8;
    while((getHeight() - (paddingBottom + paddingTop)) % numRows != 0)
        paddingTop += 1;
    float rowSpacing = float(getHeight() - (paddingBottom + paddingTop)) / float(numRows);

    int numCols = 20;
    while ((getWidth() - (paddingLeft + paddingRight)) % numCols != 0)
        paddingLeft += 1;
    float colSpacing = float(getWidth() - (paddingLeft + paddingRight)) / float(numCols);

    int startY = paddingTop;
    int endY = startY + (numRows)*rowSpacing;

    int startX = paddingLeft;
    int endX = startX + (numCols)*colSpacing;

    int rowY = startY;
    for (int i = 0; i < numRows + 1; i++)
    {

        g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
        g.drawLine(startX, rowY, endX, rowY, 1);
        rowY += rowSpacing;

    }

    int colX = startX;
    for (int i = 0; i < numCols; i++)
    {

        g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
        g.drawLine(colX, startY, colX, endY, 1);
        colX += colSpacing;

    }

    // draw final line to close off grid
    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
    g.drawLine(endX, startY, endX, endY);

}

void ADSRPlot::resized()
{

    // setBounds(getLocalBounds());
}
