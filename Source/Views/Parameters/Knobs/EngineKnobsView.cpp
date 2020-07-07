#include "EngineKnobsView.h"
EngineKnobsView::EngineKnobsView()
{

    knob1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob1.setRange(0.0, 1.0, .01);
    knob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob2.setRange(0.0, 1.0, .01);
    knob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob3.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob3.setRange(0.0, 1.0, .01);
    knob3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob4.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob4.setRange(0.0, 1.0, .01);
    knob4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    addAndMakeVisible(knob3);
    addAndMakeVisible(knob4);

    flexboxSetup();

}

void EngineKnobsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EngineKnobsView::resized()
{

    fb.performLayout (getLocalBounds().toFloat());
    float width = knob1.getWidth() / 2;
    float height = knob1.getHeight() / 6;
    knob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);

}

void EngineKnobsView::flexboxSetup()
{


    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::stretch;
    fb.alignItems = juce::FlexBox::AlignItems::stretch;

    float minWidth = 20.0f;
    float minHeight = 20.0f;
    float margin = 20.0;
    fb.items.add(juce::FlexItem(knob1).withMinWidth(minWidth).withMinHeight(minHeight)
                         .withFlex(1).withMargin(margin));

    fb.items.add(juce::FlexItem(knob2).withMinWidth(minWidth).withMinHeight(minHeight)
                         .withFlex(1).withMargin(margin));

    fb.items.add(juce::FlexItem(knob3).withMinWidth(minWidth).withMinHeight(minHeight)
                         .withFlex(1).withMargin(margin));

    fb.items.add(juce::FlexItem(knob4).withMinWidth(minWidth).withMinHeight(minHeight)
                         .withFlex(1).withMargin(margin));



}

