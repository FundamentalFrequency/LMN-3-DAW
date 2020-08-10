#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
class PluginView
    : public juce::Component,
      public juce::ApplicationCommandTarget,
      public juce::KeyListener
{

public:
    explicit PluginView(juce::ApplicationCommandManager& cm);
    ~PluginView() override;
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

    void setViewedComponent(Component* const newComponent);

    bool keyPressed(const juce::KeyPress& key, Component* originatingComponent) override;
    bool keyStateChanged(bool isKeyDown, Component *originatingComponent) override;

private:

    juce::ApplicationCommandManager& commandManager;
    juce::Component* contentComponent = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);

};


