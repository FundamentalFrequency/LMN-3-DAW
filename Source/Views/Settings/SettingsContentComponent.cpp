#include "SettingsContentComponent.h"
SettingsContentComponent::SettingsContentComponent(juce::AudioDeviceManager& deviceManager, Themes& t)
    : deviceSelectorComponent(
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
    for (auto theme : themes.themeList.objects)
    {
        themesComboBox.addItem(theme->name.get(), id);
        if (theme->name.get() == themes.currentTheme.get())
        {
            themesComboBox.setSelectedId(id);
        }
        id++;
    }

    themesComboBox.onChange = [this] {this->themes.currentTheme.setValue(themesComboBox.getText(), nullptr);};
    themesComboBoxLabel.setText("Theme:", juce::dontSendNotification);
    themesComboBoxLabel.attachToComponent(&themesComboBox, true);
    addAndMakeVisible(deviceSelectorComponent);
    addAndMakeVisible(themesComboBox);
    addAndMakeVisible(themesComboBoxLabel);



}

void SettingsContentComponent::paint(juce::Graphics& g)
{

    g.fillAll (findColour (juce::ResizableWindow::backgroundColourId));

}

void SettingsContentComponent::resized()
{

    deviceSelectorComponent.setBounds(getLocalBounds());
    themesComboBox.setBounds(getWidth() / 2 - 100, 175, 280, 25);

}

