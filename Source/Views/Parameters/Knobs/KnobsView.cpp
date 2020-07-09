#include "KnobsView.h"
#include "CommandList.h"
KnobsView::KnobsView(KnobControlledParameters* params)
    : parameters(params)
{

    knob1.addListener(this);
    knob1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob1.setRange(0.0, 1.0, .01);
    knob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob2.addListener(this);
    knob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob2.setRange(0.0, 1.0, .01);
    knob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob3.addListener(this);
    knob3.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob3.setRange(0.0, 1.0, .01);
    knob3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    knob4.addListener(this);
    knob4.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob4.setRange(0.0, 1.0, .01);
    knob4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    addAndMakeVisible(knob3);
    addAndMakeVisible(knob4);

    flexboxSetup();

    parameters->getParameter1()->addChangeListener(this);
    parameters->getParameter2()->addChangeListener(this);
    parameters->getParameter3()->addChangeListener(this);
    parameters->getParameter4()->addChangeListener(this);

}

void KnobsView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void KnobsView::resized()
{

    fb.performLayout (getLocalBounds().toFloat());
    float width = knob1.getWidth() / 2;
    float height = knob1.getHeight() / 6;
    knob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);
    knob4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, width, height);

}


void KnobsView::flexboxSetup()
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



void KnobsView::sliderValueChanged(juce::Slider* slider)
{

    // Updates model in case where user drags knob or types into its text box
    if (slider == &knob1)
    {
        parameters->getParameter1()->setValue(knob1.getValue());
    }

    if (slider == &knob2)
    {
        parameters->getParameter2()->setValue(knob2.getValue());
    }

    if (slider == &knob3)
    {
        parameters->getParameter3()->setValue(knob3.getValue());
    }

    if (slider == &knob4)
    {
        parameters->getParameter4()->setValue(knob4.getValue());
    }
}

void KnobsView::changeListenerCallback(juce::ChangeBroadcaster *source)
{

    if (source == parameters->getParameter1())
    {
        knob1.setValue(parameters->getParameter1()->getValue(), juce::dontSendNotification);
    }

    if (source == parameters->getParameter2())
    {
        knob2.setValue(parameters->getParameter2()->getValue(), juce::dontSendNotification);
    }

    if (source == parameters->getParameter3())
    {
        knob3.setValue(parameters->getParameter3()->getValue(), juce::dontSendNotification);
    }

    if (source == parameters->getParameter4())
    {
        knob4.setValue(parameters->getParameter4()->getValue(), juce::dontSendNotification);
    }

}

void KnobsView::enableKnobs()
{

    knob1.setEnabled(true);
    knob2.setEnabled(true);
    knob3.setEnabled(true);
    knob4.setEnabled(true);

}

void KnobsView::disableKnobs()
{

    knob1.setEnabled(true);
    knob2.setEnabled(true);
    knob3.setEnabled(true);
    knob4.setEnabled(true);

}

void KnobsView::currentPresetParametersChanged(KnobControlledParameters* params)
{
    parameters = params;
    repaint();
}

void KnobsView::setParameters(KnobControlledParameters* params)
{

    // remove old listeners
    parameters->getParameter1()->removeChangeListener(this);
    parameters->getParameter2()->removeChangeListener(this);
    parameters->getParameter3()->removeChangeListener(this);
    parameters->getParameter4()->removeChangeListener(this);

    parameters = params;
    parameters->getParameter1()->addChangeListener(this);
    parameters->getParameter2()->addChangeListener(this);
    parameters->getParameter3()->addChangeListener(this);
    parameters->getParameter4()->addChangeListener(this);

    knob1.setValue(parameters->getParameter1()->getValue(), juce::dontSendNotification);
    knob2.setValue(parameters->getParameter2()->getValue(), juce::dontSendNotification);
    knob3.setValue(parameters->getParameter3()->getValue(), juce::dontSendNotification);
    knob4.setValue(parameters->getParameter4()->getValue(), juce::dontSendNotification);

    repaint();

}

