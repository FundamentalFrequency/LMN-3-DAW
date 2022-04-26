#pragma once
#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
  public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor &processorRef;

    juce::Slider slider1;
    juce::Slider slider2;
    juce::Slider slider3;
    juce::Slider slider4;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        parameter1Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        parameter2Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        parameter3Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        parameter4Attachment;

    juce::FlexBox fb;

    void flexboxSetup();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        AudioPluginAudioProcessorEditor)
};
