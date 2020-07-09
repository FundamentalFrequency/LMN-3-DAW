#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "KnobControlledParameters.h"
#include "KnobsView.h"
#include "PresetSlots.h"

class EffectParametersView
    : public juce::Component,
      public juce::ApplicationCommandTarget,
      public PresetSlots::Listener
{
public:
    EffectParametersView(KnobControlledParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void currentPresetEffectParametersChanged(EffectParameters* params) override;
    
private:
    KnobControlledParameters* parameters;
    juce::Label titleLabel;
    KnobsView knobsView;
    juce::ApplicationCommandManager commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectParametersView)
};

