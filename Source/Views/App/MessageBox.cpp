#include "MessageBox.h"

MessageBox::MessageBox() {
    setLookAndFeel(&appLookAndFeel);
    addAndMakeVisible(messageLabel);
}

void MessageBox::paint(juce::Graphics &g) {
    g.fillAll(appLookAndFeel.backgroundColour);
}

void MessageBox::resized() {
    messageLabel.setBounds(getLocalBounds().reduced(20));
    messageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                    messageLabel.getHeight(),
                                    juce::Font::plain));
}

juce::String MessageBox::getMessage() { return messageLabel.getText(); }

void MessageBox::setMessage(const juce::String &message) {
    messageLabel.setText(message, juce::sendNotification);
}

juce::Font MessageBox::getFont() {
    messageLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                                    messageLabel.getHeight(),
                                    juce::Font::plain));
    return messageLabel.getFont();
}