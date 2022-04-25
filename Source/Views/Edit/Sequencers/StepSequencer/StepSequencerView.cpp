#include "StepSequencerView.h"

StepSequencerView::StepSequencerView(tracktion_engine::AudioTrack::Ptr p,
                                     app_services::MidiCommandManager &mcm)
    : viewModel(p), midiCommandManager(mcm), grid(viewModel) {

    notesPerMeasureLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1,
                   juce::Font::plain));
    notesPerMeasureLabel.setText(juce::String(viewModel.getNotesPerMeasure()),
                                 juce::dontSendNotification);
    notesPerMeasureLabel.setJustificationType(juce::Justification::centred);
    notesPerMeasureLabel.setColour(juce::Label::textColourId,
                                   appLookAndFeel.colour2);
    addAndMakeVisible(notesPerMeasureLabel);

    addAndMakeVisible(grid);
    midiCommandManager.addListener(this);
    viewModel.addListener(this);
}

StepSequencerView::~StepSequencerView() {

    viewModel.stop();
    viewModel.removeListener(this);
    midiCommandManager.removeListener(this);
}

void StepSequencerView::paint(juce::Graphics &g) {}

void StepSequencerView::resized() {

    int horizontalPadding = getWidth() / 10;
    int verticalpadding = getHeight() / 20;

    notesPerMeasureLabel.setFont(
        juce::Font(juce::Font::getDefaultMonospacedFontName(),
                   verticalpadding * 2, juce::Font::plain));
    int notesPerMeasureWidth =
        notesPerMeasureLabel.getFont().getStringWidth(
            juce::String(viewModel.getNotesPerMeasure())) +
        5;
    int notesPerMeasureX =
        double((horizontalPadding - notesPerMeasureWidth)) / 2.0;
    notesPerMeasureLabel.setBounds(notesPerMeasureX, verticalpadding * 2,
                                   notesPerMeasureWidth, verticalpadding * 2);
    grid.setBounds(horizontalPadding, verticalpadding,
                   getWidth() - 2 * horizontalPadding,
                   getHeight() - 2 * verticalpadding);
}

void StepSequencerView::noteOnPressed(int noteNumber) {

    if (midiCommandManager.isShiftDown)
        viewModel.toggleNoteNumberAtSelectedIndex(noteNumber);
}

void StepSequencerView::encoder1Increased() {

    if (midiCommandManager.isShiftDown)
        viewModel.clearNotesAtSelectedIndex();

    viewModel.incrementSelectedNoteIndex();
}

void StepSequencerView::encoder1Decreased() {

    if (midiCommandManager.isShiftDown)
        viewModel.clearNotesAtSelectedIndex();

    viewModel.decrementSelectedNoteIndex();
}

void StepSequencerView::encoder2Increased() {

    viewModel.incrementNotesPerMeasure();
}

void StepSequencerView::encoder2Decreased() {

    viewModel.decrementNotesPerMeasure();
}

void StepSequencerView::encoder3Increased() {

    viewModel.incrementNumberOfNotes();
}

void StepSequencerView::encoder3Decreased() {

    viewModel.decrementNumberOfNotes();
}

void StepSequencerView::playButtonReleased() { viewModel.play(); }

void StepSequencerView::stopButtonReleased() { viewModel.stop(); }

void StepSequencerView::notesPerMeasureChanged(int newNotesPerMeasure) {

    notesPerMeasureLabel.setText(juce::String(viewModel.getNotesPerMeasure()),
                                 juce::dontSendNotification);
    resized();
}