#include "SettingsView.h"

SettingsView::SettingsView(juce::AudioDeviceManager& deviceManager, app_models::Themes& t)
    : themes(t),
      settingsContentComponent(deviceManager, themes)
{

    settingsViewport.setViewedComponent (&settingsContentComponent, false);
    addAndMakeVisible(settingsViewport);

}

void SettingsView::paint(juce::Graphics& g)
{

}

void SettingsView::resized()
{

    auto r = getLocalBounds();
    auto scrollBarWidth = getLookAndFeel().getDefaultScrollbarWidth();
    settingsContentComponent.setSize(juce::jmax (r.getWidth() - scrollBarWidth, settingsContentComponent.getMinimumWidth()),
                          juce::jmax(r.getHeight(), settingsContentComponent.getMinimumHeight()));
    settingsViewport.setBounds(r);


}

