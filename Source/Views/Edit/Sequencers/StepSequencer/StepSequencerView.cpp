#include "StepSequencerView.h"

StepSequencerView::StepSequencerView(tracktion_engine::AudioTrack::Ptr p, app_services::MidiCommandManager& mcm)
    : viewModel(p),
      midiCommandManager(mcm)
{

    addAndMakeVisible(grid);

}

StepSequencerView::~StepSequencerView()
{

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