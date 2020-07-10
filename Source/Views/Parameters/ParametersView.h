#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>

class ParametersView
    : public juce::Component,
      public juce::ApplicationCommandTarget

{
public:
    ParametersView(app_models::KnobControlledParameters* params);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;
    
private:
    app_models::KnobControlledParameters* parameters;
    juce::ApplicationCommandManager commandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParametersView)
};

