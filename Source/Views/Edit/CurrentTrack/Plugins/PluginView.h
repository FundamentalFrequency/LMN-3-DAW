#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
class PluginView
    : public juce::Component,
      public juce::ApplicationCommandTarget
{

public:
    PluginView();
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:

    juce::Label titleLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);

};


