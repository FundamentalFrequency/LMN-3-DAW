#include "OctaveDisplayComponent.h"
OctaveDisplayComponent::OctaveDisplayComponent()
{

}

void OctaveDisplayComponent::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.backgroundColour);
    g.fillRect(getLocalBounds());
    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .75, juce::Font::plain);


    juce::Font fontAudioFont = sharedFontAudio->getFont(getHeight() * 0.75f);



    juce::String octaveText = juce::String(octaveInt);
    int totalTextWidth = fontAudioFont.getStringWidth(keyboardIcon) + 1 + font.getStringWidth(octaveText);


    int keyboardX = (getWidth() - totalTextWidth) / 2;
    int octaveX = keyboardX + fontAudioFont.getStringWidth(keyboardIcon) + 1;

    g.setFont(fontAudioFont);
    g.setColour(appLookAndFeel.whiteColour);
    g.drawText(keyboardIcon, keyboardX, (getHeight() - fontAudioFont.getHeight()) / 2,
               fontAudioFont.getStringWidth(keyboardIcon), fontAudioFont.getHeight(), juce::Justification::centred);


    if (octaveInt >= 0) {

        octaveText = "+" + octaveText;
        g.setColour(appLookAndFeel.greenColour);

    }
    else {
        g.setColour(appLookAndFeel.redColour);
    }

    g.setFont(font);
    g.drawText(octaveText, octaveX, (getHeight() - font.getHeight()) / 2,
               font.getStringWidth(octaveText), font.getHeight(), juce::Justification::centred);



}
void OctaveDisplayComponent::resized()
{

}

void OctaveDisplayComponent::setOctave(int octave)
{

    octaveInt = octave;
    repaint();

}