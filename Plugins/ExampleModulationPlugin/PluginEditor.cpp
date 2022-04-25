#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {
    juce::ignoreUnused(processorRef);

    slider1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider1.setRange(0.0, 1.0, .01);
    slider1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, 0, 0);
    parameter1Attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.state, processorRef.parameter1Id, slider1);

    slider2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider2.setRange(0.0, 1.0, .01);
    slider2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, 0, 0);
    parameter2Attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.state, processorRef.parameter2Id, slider2);

    slider3.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider3.setRange(0.0, 1.0, .01);
    slider3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, 0, 0);
    parameter3Attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.state, processorRef.parameter3Id, slider3);

    slider4.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider4.setRange(0.0, 1.0, .01);
    slider4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, 0, 0);
    parameter4Attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.state, processorRef.parameter4Id, slider4);

    addAndMakeVisible(slider1);
    addAndMakeVisible(slider2);
    addAndMakeVisible(slider3);
    addAndMakeVisible(slider4);

    // since we are showing the editor, change the processor value to true
    processorRef.state.getParameter(processorRef.editorIsVisibleId)
        ->setValueNotifyingHost(true);

    flexboxSetup();
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, false);
    setSize(400, 300);
    setWantsKeyboardFocus(false);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {

    // since we are closing the editor, change the processor value to false
    processorRef.state.getParameter(processorRef.editorIsVisibleId)
        ->setValueNotifyingHost(false);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with
    // a solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized() {
    fb.performLayout(getLocalBounds().toFloat());
    int width = slider1.getWidth() / 2;
    int height = slider1.getHeight() / 6;
    slider1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, width, height);
    slider2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, width, height);
    slider3.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, width, height);
    slider4.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            true, width, height);
}

void AudioPluginAudioProcessorEditor::flexboxSetup() {
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.flexDirection = juce::FlexBox::Direction::row;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::stretch;
    fb.alignItems = juce::FlexBox::AlignItems::stretch;

    float minWidth = 20.0f;
    float minHeight = 20.0f;
    float margin = 20.0;
    fb.items.add(juce::FlexItem(slider1)
                     .withMinWidth(minWidth)
                     .withMinHeight(minHeight)
                     .withFlex(1)
                     .withMargin(margin));

    fb.items.add(juce::FlexItem(slider2)
                     .withMinWidth(minWidth)
                     .withMinHeight(minHeight)
                     .withFlex(1)
                     .withMargin(margin));

    fb.items.add(juce::FlexItem(slider3)
                     .withMinWidth(minWidth)
                     .withMinHeight(minHeight)
                     .withFlex(1)
                     .withMargin(margin));

    fb.items.add(juce::FlexItem(slider4)
                     .withMinWidth(minWidth)
                     .withMinHeight(minHeight)
                     .withFlex(1)
                     .withMargin(margin));
}
