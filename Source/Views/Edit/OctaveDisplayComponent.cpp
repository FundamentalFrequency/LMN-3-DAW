#include "OctaveDisplayComponent.h"
OctaveDisplayComponent::OctaveDisplayComponent() {}

void OctaveDisplayComponent::paint(juce::Graphics &g) {
    auto icon = juce::String::charToString(0xf001);
    g.setColour(appLookAndFeel.backgroundColour);
    g.fillRect(getLocalBounds());
    juce::Font font(juce::Font::getDefaultMonospacedFontName(),
                    getHeight() * .75, juce::Font::plain);
    fontAwesomeFont.setHeight(getHeight() * .5);
    juce::String octaveText = juce::String(octaveInt);
    int totalTextWidth = fontAwesomeFont.getStringWidth(icon) + 5 +
                         font.getStringWidth(octaveText);

    int keyboardX = (getWidth() - totalTextWidth) / 2;
    int octaveX = keyboardX + fontAwesomeFont.getStringWidth(icon) + 5;

    g.setFont(fontAwesomeFont);
    g.setColour(appLookAndFeel.whiteColour);
    g.drawText(icon, keyboardX, (getHeight() - fontAwesomeFont.getHeight()) / 2,
               fontAwesomeFont.getStringWidth(icon),
               fontAwesomeFont.getHeight(), juce::Justification::centred);

    if (octaveInt >= 0) {
        octaveText = "+" + octaveText + " ";
        g.setColour(appLookAndFeel.greenColour);

    } else {
        g.setColour(appLookAndFeel.redColour);
    }

    g.setFont(font);
    g.drawText(octaveText, octaveX, (getHeight() - font.getHeight()) / 2,
               font.getStringWidth(octaveText), font.getHeight(),
               juce::Justification::centred);
}
void OctaveDisplayComponent::resized() {}

void OctaveDisplayComponent::setOctave(int octave) {
    octaveInt = octave;
    repaint();
}