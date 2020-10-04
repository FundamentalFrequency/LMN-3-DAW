#include "SettingsView.h"

SettingsView::SettingsView(juce::AudioDeviceManager& deviceManager)
    : settingsContentComponent(deviceManager)
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

