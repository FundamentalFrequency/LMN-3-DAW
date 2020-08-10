#include "SettingsContentComponent.h"

SettingsContentComponent::SettingsContentComponent(juce::AudioDeviceManager& dm, app_models::Themes& t)
    : deviceManager(dm),
      deviceSelectorComponent(
        deviceManager,
        0,
        256,
        0,
        256,
        true,
        false,
        false,
        false),
      themes(t)
{

    int id = 1;
    for (auto themeName : themes.getThemeNames())
    {
        themesComboBox.addItem(themeName, id);
        if (themeName == themes.getCurrentTheme()->getName())
        {
            themesComboBox.setSelectedId(id);
        }
        id++;
    }

    themesComboBox.onChange = [this] {themes.setCurrentThemeName(themesComboBox.getText());};
    themesComboBoxLabel.attachToComponent(&themesComboBox, true);
    addAndMakeVisible(deviceSelectorComponent);
    addAndMakeVisible(themesComboBox);
    addAndMakeVisible(themesComboBoxLabel);
    addAndMakeVisible(graphicsTitleLabel);
    addAndMakeVisible(audioTitleLabel);

    deviceManager.addChangeListener(this);



}

void SettingsContentComponent::paint(juce::Graphics& g)
{

    g.fillAll (findColour (juce::ResizableWindow::backgroundColourId));

}

void SettingsContentComponent::resized()
{

    auto bounds = getLocalBounds();
    auto space = itemHeight / 4;
    graphicsTitleLabel.setBounds(bounds.removeFromTop(itemHeight));
    bounds.removeFromTop(space);

    auto xPos = (float) bounds.getX() + ((float) bounds.getWidth() * 0.35f);
    auto width = (float) bounds.getWidth() * 0.6f;
    themesComboBox.setBounds (bounds.removeFromTop (itemHeight).withWidth ((int) width).withX ((int) xPos));
    bounds.removeFromTop (space);

    audioTitleLabel.setBounds(bounds.removeFromTop (itemHeight));
    bounds.removeFromTop (space);
    deviceSelectorComponent.setBounds(bounds);

}

void SettingsContentComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{

    if (source == dynamic_cast<juce::ChangeBroadcaster*>(&deviceManager))
    {
        repaint();
    }

}

