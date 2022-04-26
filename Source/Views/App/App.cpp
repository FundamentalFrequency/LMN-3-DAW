#include "App.h"
#include "TrackView.h"
#include "TracksView.h"
#include <SynthSampleData.h>

App::App(tracktion_engine::Edit &e, app_services::MidiCommandManager &mcm,
         juce::ValueTree v)
    : edit(e), midiCommandManager(mcm),
      editTabBarView(edit, midiCommandManager) {
    // add the application state to the edit state tree
    edit.state.addChild(v, -1, nullptr);
    edit.setTimecodeFormat(tracktion_engine::TimecodeType::millisecs);

    setSize(800, 480);

    setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(editTabBarView);

    midiCommandManager.addListener(this);
    addAndMakeVisible(progressView);
    progressView.setVisible(false);
}

App::~App() {
    setLookAndFeel(nullptr);
    midiCommandManager.removeListener(this);
}

void App::paint(juce::Graphics &g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void App::resized() {
    progressView.setBounds(
        getLocalBounds().reduced(getWidth() / 2.25, getHeight() / 2.25));
    editTabBarView.setBounds(getLocalBounds());
}

void App::showProgressView() { progressView.setVisible(true); }
void App::hideProgressView() { progressView.setVisible(false); }
