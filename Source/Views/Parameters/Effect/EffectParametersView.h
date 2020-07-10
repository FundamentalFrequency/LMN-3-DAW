#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>
#include "KnobsView.h"


class EffectParametersView
    : public juce::Component,
      public juce::ApplicationCommandTarget,
      public app_models::PresetSlots::Listener
{
public:
    EffectParametersView(app_models::KnobControlledParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void currentPresetEffectParametersChanged(app_models::EffectParameters* params) override;
    
private:
    app_models::KnobControlledParameters* parameters;
    juce::Label titleLabel;
    KnobsView knobsView;
    juce::ApplicationCommandManager commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectParametersView)
};

