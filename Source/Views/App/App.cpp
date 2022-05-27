#include "App.h"
#include "TrackView.h"
#include <app_configuration/app_configuration.h>

App::App(tracktion_engine::Edit &e, app_services::MidiCommandManager &mcm)
    : edit(e), midiCommandManager(mcm),
      editTabBarView(edit, midiCommandManager) {
    edit.setTimecodeFormat(tracktion_engine::TimecodeType::millisecs);

    auto userAppDataDirectory = juce::File::getSpecialLocation(
        juce::File::userApplicationDataDirectory);
    auto configFile =
        userAppDataDirectory.getChildFile(JUCE_APPLICATION_NAME_STRING)
            .getChildFile("config.yaml");
    auto width = int(ConfigurationHelpers::getWidth(configFile));
    auto height = int(ConfigurationHelpers::getHeight(configFile));
    setSize(width, height);

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
