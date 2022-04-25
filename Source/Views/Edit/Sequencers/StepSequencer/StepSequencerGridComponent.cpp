#include "StepSequencerGridComponent.h"

StepSequencerGridComponent::StepSequencerGridComponent(
    app_view_models::StepSequencerViewModel &vm)
    : viewModel(vm) {

    viewModel.addListener(this);
}

StepSequencerGridComponent::~StepSequencerGridComponent() {

    viewModel.removeListener(this);
}

void StepSequencerGridComponent::paint(juce::Graphics &g) {

    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));

    float paddingTop = 4;
    float paddingBottom = 4;
    float paddingLeft = 4;
    float paddingRight = 4;

    // draw lines for rows and cols
    // have to make sure it divides evenly, increase padding a bit until it does
    int numRows = 24;
    while (int(float(getHeight()) - (paddingBottom + paddingTop)) % numRows !=
           0)
        paddingTop += 1;
    float rowSpacing =
        (float(getHeight()) - (paddingBottom + paddingTop)) / float(numRows);

    int numCols = 16;
    while (int((float(getWidth()) - (paddingLeft + paddingRight))) % numCols !=
           0)
        paddingLeft += 1;
    float colSpacing =
        (float(getWidth()) - (paddingLeft + paddingRight)) / float(numCols);

    float startY = paddingTop;
    float endY = startY + float(numRows) * rowSpacing;

    float startX = paddingLeft;
    float endX = startX + float(numCols) * colSpacing;

    float rowY = startY;
    for (int i = 0; i < numRows + 1; i++) {

        g.drawLine(startX, rowY, endX, rowY, 1);
        rowY += rowSpacing;
    }

    float colX = startX;
    for (int i = 0; i < viewModel.getNumberOfNotes(); i++) {

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
    for (int channelNumber = 0; channelNumber < viewModel.getNumChannels();
         channelNumber++) {
        float noteX = startX;
        for (int noteIndex = 0; noteIndex < viewModel.getNumNotesPerChannel();
             noteIndex++) {

            if (viewModel.hasNoteAt(channelNumber, noteIndex)) {

                if (noteIndex < viewModel.getNumberOfNotes()) {

                    g.setColour(appLookAndFeel.yellowColour);
                    g.fillRect(noteX, channelY, colSpacing, rowSpacing);

                } else {

                    g.setColour(appLookAndFeel.colour3.withAlpha(.3f));
                    g.fillRect(noteX, channelY, colSpacing, rowSpacing);
                }
            }

            noteX += colSpacing;
        }

        channelY -= rowSpacing;
    }

    // draw index marker
    g.setColour(appLookAndFeel.colour1);
    float lineThickness = 3.0f;
    g.drawRect(float(startX - (lineThickness / 2) +
                     float(viewModel.getSelectedNoteIndex()) * colSpacing),
               float(startY) - (lineThickness / 2),
               float(colSpacing) + (lineThickness),
               float(endY - startY) + (lineThickness), lineThickness);
}

void StepSequencerGridComponent::resized() {}

void StepSequencerGridComponent::patternChanged() {

    resized();
    repaint();
}

void StepSequencerGridComponent::selectedNoteIndexChanged(int newIndex) {

    resized();
    repaint();
}

void StepSequencerGridComponent::numberOfNotesChanged(int newNumberOfNotes) {

    resized();
    repaint();
}

void StepSequencerGridComponent::notesPerMeasureChanged(
    int newNotesPerMeasure) {

    resized();
    repaint();
}
