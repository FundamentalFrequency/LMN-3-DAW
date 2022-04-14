#include "StepSequencerGridComponent.h"

StepSequencerGridComponent::StepSequencerGridComponent(app_view_models::StepSequencerViewModel& vm)
    : viewModel(vm)
{

    viewModel.addListener(this);

}

StepSequencerGridComponent::~StepSequencerGridComponent()
{

    viewModel.removeListener(this);

}

void StepSequencerGridComponent::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));

    int paddingTop = 4;
    int paddingBottom = 4;
    int paddingLeft = 4;
    int paddingRight = 4;

    // draw lines for rows and cols
    // have to make sure it divides evenly, increase padding a bit until it does
    int numRows = 24;
    while((getHeight() - (paddingBottom + paddingTop)) % numRows != 0)
        paddingTop += 1;
    float rowSpacing = float(getHeight() - (paddingBottom + paddingTop)) / float(numRows);

    int numCols = 16;
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

        g.drawLine(startX, rowY, endX, rowY, 1);
        rowY += rowSpacing;

    }

    int colX = startX;
    for (int i = 0; i < viewModel.getNumberOfNotes(); i++)
    {

        if (i % viewModel.getNotesPerMeasure() == 0)
            g.setColour(juce::Colours::white.withAlpha(.6f));
        else
            g.setColour(appLookAndFeel.colour3.withAlpha(.3f));

        g.drawLine(colX, startY, colX, endY, 1);
        colX += colSpacing;

    }

    // draw final line to close off grid
    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
    g.drawLine(endX, startY, endX, endY);

    // draw rectangles for notes
    float channelY = endY - rowSpacing;
    for (int channelNumber = 0; channelNumber < viewModel.getNumChannels(); channelNumber++)
    {
        float noteX = startX;
        for (int noteIndex= 0; noteIndex < viewModel.getNumNotesPerChannel(); noteIndex++)
        {

            float noteRadius = 4;


            if (viewModel.hasNoteAt(channelNumber, noteIndex))
            {

                if (noteIndex < viewModel.getNumberOfNotes())
                {

                    g.setColour(appLookAndFeel.yellowColour);
                    g.fillRect(noteX, channelY, colSpacing, rowSpacing);

                }
                else
                {

                    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
                    g.fillRect(noteX, channelY, colSpacing, rowSpacing);

                }

            }

            noteX += colSpacing;
        }

        channelY -= rowSpacing;

    }

    // draw index marker
    g.setColour(juce::Colours::white);
    g.drawRect(float(startX + viewModel.getSelectedNoteIndex()*colSpacing), float(startY), float(colSpacing), float(endY - startY));
}

void StepSequencerGridComponent::resized()
{


}

void StepSequencerGridComponent::patternChanged()
{

    resized();
    repaint();

}

void StepSequencerGridComponent::selectedNoteIndexChanged(int newIndex)
{

    resized();
    repaint();

}

void StepSequencerGridComponent::numberOfNotesChanged(int newNumberOfNotes)
{

    resized();
    repaint();

}

void StepSequencerGridComponent::notesPerMeasureChanged(int newNotesPerMeasure)
{

    resized();
    repaint();

}


