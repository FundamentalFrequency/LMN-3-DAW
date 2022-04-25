#include "AppLookAndFeel.h"
#include <yaml-cpp/yaml.h>
#include "SimpleListItemView.h"

AppLookAndFeel::AppLookAndFeel() {
    readColoursFromConfig();

    setColour(juce::DocumentWindow::backgroundColourId, backgroundColour);

    setColour(juce::TabbedComponent::backgroundColourId, backgroundColour);

    setColour(juce::Label::textColourId, textColour);

    setColour(juce::ListBox::backgroundColourId, backgroundColour);

    setColour(SimpleListItemView::unselectedBackgroundColourId, backgroundColour);
    setColour(SimpleListItemView::selectedBackgroundColourId, colour1);
    setColour(SimpleListItemView::unselectedTextColourId, colour1);
    setColour(SimpleListItemView::selectedTextColourId, backgroundColour);

    setColour(juce::ScrollBar::thumbColourId, colour1);
    setColour(juce::ScrollBar::trackColourId, colour2);
}

void AppLookAndFeel::readColoursFromConfig() {
    // Read the colors.yaml config file and overwrite the default colours (if appropriate config is found)
    auto userAppDataDirectory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    auto coloursFile = userAppDataDirectory.getChildFile(JUCE_APPLICATION_NAME_STRING)
            .getChildFile("colours.yaml");
    if (coloursFile.existsAsFile()) {
        YAML::Node rootNode = YAML::LoadFile(coloursFile.getFullPathName().toStdString());
        if (rootNode) {
            YAML::Node coloursNode = rootNode["colours"];
            if (coloursNode) {
                if (coloursNode["backgroundColour"]) {
                    backgroundColour = juce::Colour::fromString(coloursNode["backgroundColour"].as<std::string>());
                }

                if (coloursNode["textColour"]) {
                    textColour = juce::Colour::fromString(coloursNode["textColour"].as<std::string>());
                }

                if (coloursNode["colour1"]) {
                    colour1 = juce::Colour::fromString(coloursNode["colour1"].as<std::string>());
                }

                if (coloursNode["colour2"]) {
                    colour2 = juce::Colour::fromString(coloursNode["colour2"].as<std::string>());
                }

                if (coloursNode["colour3"]) {
                    colour3 = juce::Colour::fromString(coloursNode["colour3"].as<std::string>());
                }

                if (coloursNode["colour4"]) {
                    colour4 = juce::Colour::fromString(coloursNode["colour4"].as<std::string>());
                }

                if (coloursNode["colour5"]) {
                    colour5 = juce::Colour::fromString(coloursNode["colour5"].as<std::string>());
                }

                if (coloursNode["colour6"]) {
                    colour6 = juce::Colour::fromString(coloursNode["colour6"].as<std::string>());
                }

                if (coloursNode["colour7"]) {
                    colour7 = juce::Colour::fromString(coloursNode["colour7"].as<std::string>());
                }

                if (coloursNode["colour8"]) {
                    colour8 = juce::Colour::fromString(coloursNode["colour8"].as<std::string>());
                }
            }
        }
    }
}