#pragma once
#include <app_services/app_services.h>
#include <juce_gui_basics/juce_gui_basics.h>
class PluginView : public juce::Component,
                   public app_services::MidiCommandManager::Listener {
  public:
    explicit PluginView(app_services::MidiCommandManager &mcm,
                        tracktion::Plugin::Ptr p, Component *pluginComp);
    ~PluginView() override;
    void paint(juce::Graphics &) override;
    void resized() override;
    tracktion::Plugin::Ptr getPlugin();

  private:
    app_services::MidiCommandManager &midiCommandManager;
    tracktion::Plugin::Ptr plugin;
    juce::Component::SafePointer<juce::Component> pluginComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginView);
};
