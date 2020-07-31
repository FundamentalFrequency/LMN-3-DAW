#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>

class LFOParametersView
    : public juce::Component,
      public juce::ApplicationCommandTarget,
      public app_models::PresetSlots::Listener
{
public:
    LFOParametersView(app_models::KnobControlledParameters* params, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void currentPresetLFOParametersChanged(app_models::LFOParameters* params) override;
    
private:
    app_models::KnobControlledParameters* parameters;
    juce::Label titleLabel;
    juce::ApplicationCommandManager& commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOParametersView)
};

