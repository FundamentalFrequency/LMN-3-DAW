#include "OctaveDisplayComponent.h"
OctaveDisplayComponent::OctaveDisplayComponent()
{

}

void OctaveDisplayComponent::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.backgroundColour);
    g.fillRect(getLocalBounds());
    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .75, juce::Font::plain);


    juce::String octaveText = juce::String(octaveInt);
    int totalTextWidth = font.getStringWidth(octaveText);

    int octaveX = 0;
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