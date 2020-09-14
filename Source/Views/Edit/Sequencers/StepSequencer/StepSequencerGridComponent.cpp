#include "StepSequencerGridComponent.h"

StepSequencerGridComponent::StepSequencerGridComponent(app_view_models::StepSequencerViewModel& vm)
    : viewModel(vm)
{

    viewModel.addListener(this);
    viewModel.noteIndexMarkerState.addListener(this);

}

StepSequencerGridComponent::~StepSequencerGridComponent()
{

    viewModel.removeListener(this);
    viewModel.noteIndexMarkerState.removeListener(this);
}

void StepSequencerGridComponent::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));

    int padding = 4;

    // draw lines for rows and cols
    int numRows = (viewModel.getNumChannels() / 2) + 1;
    float rowSpacing = (getHeight() - 2*padding) / numRows;

    int numCols = viewModel.getNumNotesPerChannel() + 1;
    float colSpacing = (getWidth() - 2*padding) / numCols;

    int startY = padding;
    int endY = startY + (numRows-1)*rowSpacing;

    int startX = padding;
    int endX = startX + (numCols-1)*colSpacing;

    int rowY = startY;
    for (int i = 0; i < numRows; i++)
    {

        g.drawLine(startX, rowY, endX, rowY, 1);
        rowY += rowSpacing;

    }

    int colX = startX;
    for (int i = 0; i < numCols; i++)
    {

        if (i % 4 == 0)
            g.setColour(appLookAndFeel.colour1.withAlpha(.3f));
        else
            g.setColour(appLookAndFeel.colour3.withAlpha(.3f));

        g.drawLine(colX, startY, colX, endY, 1);
        colX += colSpacing;

    }

    // draw index marker
    g.setColour(juce::Colours::white);
    g.drawLine(startX + viewModel.noteIndexMarkerState.getSelectedItemIndex()*colSpacing, startY, startX + viewModel.noteIndexMarkerState.getSelectedItemIndex()*colSpacing, endY);

    // draw dots for notes
    float channelY = endY;
    for (int channelNumber = 0; channelNumber < viewModel.getNumChannels(); channelNumber++)
    {
        float noteX = startX;
        for (int noteNumber = 0; noteNumber < viewModel.getNumNotesPerChannel(); noteNumber++)
        {

            float noteRadius = 2;
            g.setColour(juce::Colours::greenyellow);

            if (viewModel.hasNoteAt(channelNumber, noteNumber))
                g.fillEllipse(noteX - noteRadius, channelY - noteRadius, 2*noteRadius, 2*noteRadius);

            noteX += colSpacing;
        }

        channelY -= rowSpacing / 2.0;

    }

}

void StepSequencerGridComponent::resized()
{

}

void StepSequencerGridComponent::patternChanged()
{

    resized();
    repaint();

}

void StepSequencerGridComponent::selectedIndexChanged(int newIndex)
{

    resized();
    repaint();
}


