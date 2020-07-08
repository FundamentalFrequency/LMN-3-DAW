#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "EngineKnobsView.h"
#include "EngineParameters.h"
#include "PresetSlots.h"

class SynthEngineParametersView
    : public juce::Component,
      public juce::ApplicationCommandTarget,
      public PresetSlots::Listener

{
public:
    SynthEngineParametersView(EngineParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void currentPresetEngineParametersChanged(EngineParameters* params) override;

    
private:

    EngineParameters* parameters;
    juce::Label titleLabel;
    EngineKnobsView knobsView;
    juce::ApplicationCommandManager commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthEngineParametersView)
};

