#include "LabeledKnob.h"

LabeledKnob::LabeledKnob() {
    knob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob.setRange(0.0, 1.0, .01);
    knob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
                         0, 0);
    knob.setColour(knob.textBoxOutlineColourId,
                   juce::Colours::red.withAlpha(0.0f));
    knob.setColour(knob.textBoxTextColourId, appLookAndFeel.textColour);
    addAndMakeVisible(knob);

    label.setText("parameter", juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void LabeledKnob::paint(juce::Graphics &g) {}

void LabeledKnob::resized() {
    knob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
                         getWidth() * .5, getHeight() * labelHeight);
    label.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(),
                             getHeight() * labelHeight * .7,
                             juce::Font::plain));
    label.setBoundsRelative(0.f, 0.f, 1.f, labelHeight);
    knob.setBoundsRelative(0.f, labelHeight, 1.f, sliderHeight);
}

juce::Slider &LabeledKnob::getSlider() { return knob; }

juce::Label &LabeledKnob::getLabel() { return label; }
