#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
class PluginView
    : public juce::Component,
      public juce::ApplicationCommandTarget
{

public:
    PluginView(juce::ApplicationCommandManager& cm);
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void setViewedComponent(Component* const newComponent);

private:

    juce::ApplicationCommandManager& commandManager;
    juce::WeakReference<Component> contentComponent;

    void deleteContentComponent();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);

};


