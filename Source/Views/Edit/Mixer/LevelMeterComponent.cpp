#include "LevelMeterComponent.h"

LevelMeterComponent::LevelMeterComponent(tracktion::LevelMeasurer &lm, int chan)
    : channel(chan), levelMeasurer(lm) {
    prevLeveldB = currentLeveldB;
    currentLeveldB = levelClient.getAndClearAudioLevel(channel).dB;
    setOpaque(true);
    levelMeasurer.addClient(levelClient);
    startTimerHz(120);
}

LevelMeterComponent::~LevelMeterComponent() {
    levelMeasurer.removeClient(levelClient);
    stopTimer();
}
void LevelMeterComponent::paint(juce::Graphics &g) {
    g.fillAll(
        juce::Colour(appLookAndFeel.blackColour)); // fill the background black

    const double meterHeight{double(getHeight())};
    const double meterWidth{double(getWidth())};
    const double offSet{fabs(RANGEMINdB)};
    const double scaleFactor{meterHeight / (RANGEMAXdB + offSet)};

    // draw meter Gain bar
    g.setColour(appLookAndFeel.greenColour);
    if (currentLeveldB >= 0.0) {
        g.setColour(appLookAndFeel.redColour);
    }
    auto displayBarHeight = ((currentLeveldB + offSet) * scaleFactor);

    if (displayBarHeight > 0) {
        g.fillRect(0.0f, float(meterHeight - displayBarHeight),
                   float(meterWidth), float(displayBarHeight));
    }

    // now we calculate and draw our 0dB line
    g.setColour(appLookAndFeel.whiteColour); // set line color
    g.fillRect(0.0f, float(meterHeight - (offSet * scaleFactor)),
               float(meterWidth), 1.0f);
}

void LevelMeterComponent::timerCallback() {
    prevLeveldB = currentLeveldB;

    currentLeveldB = levelClient.getAndClearAudioLevel(channel).dB;

    // Now we give the level bar fading charcteristics.
    // And, the below coversions, decibelsToGain and gainToDecibels,
    // take care of 0dB, which will never fade!...but a gain of 1.0 (0dB) will.

    const auto prevLevel{juce::Decibels::decibelsToGain(prevLeveldB)};

    if (prevLeveldB > currentLeveldB) {
        currentLeveldB = juce::Decibels::gainToDecibels(prevLevel * 0.94);
    }

    // the test below may save some unnecessary paints
    if (currentLeveldB != prevLeveldB) {
        repaint();
    }
}