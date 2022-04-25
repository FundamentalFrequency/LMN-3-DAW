#include "ADSRPlot.h"

void ADSRPlot::paint(juce::Graphics& g)
{

    int paddingTop = 4;
    int paddingBottom = 4;
    int paddingLeft = 4;
    int paddingRight = 4;

    // draw lines for rows and cols
    // have to make sure it divides evenly, increase padding a bit until it does
    int numRows = 12;
    while((getHeight() - (paddingBottom + paddingTop)) % numRows != 0)
        paddingTop += 1;
    float rowSpacing = float(getHeight() - (paddingBottom + paddingTop)) / float(numRows);

    int numCols = 24;
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

    float sectionWidth = (endX - startX) * .33333333;
    float sectionHeight = getHeight() - paddingBottom - paddingTop;
    float markerRadius = 4;
    g.setColour(juce::Colours::limegreen);
    juce::Point<int> point1(paddingLeft, getHeight() - paddingBottom);
    juce::Point<int> point2(point1.x + (sectionWidth * attackValue), paddingTop);
    juce::Point<int> point3(point2.x + (sectionWidth * decayValue), point2.y + (sectionHeight* (1-sustainValue)));
    juce::Point<int> point4(point3.x + (sectionWidth * releaseValue), getHeight() - paddingBottom);

    g.fillEllipse(point1.x - markerRadius, point1.y - markerRadius, 2*markerRadius, 2*markerRadius);
    g.fillEllipse(point2.x - markerRadius, point2.y - markerRadius, 2*markerRadius, 2*markerRadius);
    g.fillEllipse(point3.x - markerRadius, point3.y - markerRadius, 2*markerRadius, 2*markerRadius);
    g.fillEllipse(point4.x - markerRadius, point4.y - markerRadius, 2*markerRadius, 2*markerRadius);

    g.drawLine(point1.x, point1.y, point2.x, point2.y, 2);
    g.drawLine(point2.x, point2.y, point3.x, point3.y, 2);
    g.drawLine(point3.x, point3.y, point4.x, point4.y, 2);



}

void ADSRPlot::resized()
{


}
