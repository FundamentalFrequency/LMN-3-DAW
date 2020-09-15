#include "StepSequencerView.h"

StepSequencerView::StepSequencerView(tracktion_engine::AudioTrack::Ptr p, app_services::MidiCommandManager& mcm)
    : viewModel(p),
      midiCommandManager(mcm),
      grid(viewModel)
{

    addAndMakeVisible(grid);
    midiCommandManager.addListener(this);

}

StepSequencerView::~StepSequencerView()
{

    midiCommandManager.removeListener(this);
}

void StepSequencerView::paint(juce::Graphics& g)
{


}

void StepSequencerView::resized()
{

    int horizontalPadding = getWidth() / 10;
    int verticalpadding = getHeight() / 20;

    grid.setBounds(horizontalPadding, verticalpadding, getWidth() - 2*horizontalPadding, getHeight() - 2*verticalpadding);

}

void StepSequencerView::noteOnPressed(int noteNumber)
{

    viewModel.toggleNoteNumberAtSelectedIndex(noteNumber);

}

void StepSequencerView::encoder1Increased()
{

    if (midiCommandManager.isShiftDown)
        viewModel.clearNotesAtSelectedIndex();

    viewModel.incrementSelectedNoteIndex();

}

void StepSequencerView::encoder1Decreased()
{

    if (midiCommandManager.isShiftDown)
        viewModel.clearNotesAtSelectedIndex();

    viewModel.decrementSelectedNoteIndex();

}

void StepSequencerView::encoder3Increased()
{

    viewModel.incrementNumberOfNotes();

}

void StepSequencerView::encoder3Decreased()
{

    viewModel.decrementNumberOfNotes();
}