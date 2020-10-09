#include "OctaveDisplayComponent.h"
OctaveDisplayComponent::OctaveDisplayComponent()
{

}

void OctaveDisplayComponent::paint(juce::Graphics& g)
{

    g.fillAll(appLookAndFeel.backgroundColour.withAlpha(0.0f));
    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .75, juce::Font::plain);
    g.setFont(font);

    juce::String octaveText = juce::String(octaveInt);
    if (octaveInt >= 0) {

        octaveText = "+" + octaveText;
        g.setColour(appLookAndFeel.greenColour);

    }
    else {
        g.setColour(appLookAndFeel.redColour);
    }

    g.drawText(octaveText, (getWidth() - font.getStringWidthFloat(octaveText)) / 2, (getHeight() - font.getHeight()) / 2,
               font.getStringWidthFloat(octaveText), font.getHeight(), juce::Justification::centred);


}
void OctaveDisplayComponent::resized()
{

}

void OctaveDisplayComponent::setOctave(int octave)
{

    octaveInt = octave;
    repaint();

}