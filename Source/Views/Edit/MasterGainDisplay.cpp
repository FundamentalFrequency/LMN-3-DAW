#include "MasterGainDisplay.h"

MasterGainDisplay::MasterGainDisplay()
{

}

void MasterGainDisplay::paint(juce::Graphics& g)
{

    g.setColour(appLookAndFeel.backgroundColour);
    g.fillRect(getLocalBounds());
    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .75, juce::Font::plain);
    g.setFont(font);

    juce::String gainText = "Volume: " +  juce::String(gain) + "%";
    g.setColour(appLookAndFeel.redColour);


    g.drawText(gainText, (getWidth() - font.getStringWidthFloat(gainText)) / 2, (getHeight() - font.getHeight()) / 2,
               font.getStringWidthFloat(gainText), font.getHeight(), juce::Justification::centred);


}
void MasterGainDisplay::resized()
{

}

void MasterGainDisplay::setGain(int gain)
{

    this->gain = gain;
    repaint();

}