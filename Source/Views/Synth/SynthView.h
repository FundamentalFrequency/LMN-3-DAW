#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <memory>
#include "SynthEngineParametersView.h"
#include "ADSRParametersView.h"
#include "EffectParametersView.h"
#include "LFOParametersView.h"
#include "Views/List/Engine/Synth/SynthEngineListView.h"

class SynthView : public juce::TabbedComponent,
                  public juce::ApplicationCommandTarget

{
public:
    SynthView(tracktion_engine::Engine& e, app_models::PresetSlots& ps, juce::ApplicationCommandManager& cm);

    [[noreturn]] ~SynthView();

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

private:

    tracktion_engine::Engine& engine;
    app_models::PresetSlots& presetSlots;
    juce::ApplicationCommandManager& commandManager;
    std::unique_ptr<SynthEngineParametersView> synthEngineParametersView;
    std::unique_ptr<ADSRParametersView> adsrParametersView;
    std::unique_ptr<EffectParametersView> effectParametersView;
    std::unique_ptr<LFOParametersView> lfoParametersView;
    std::unique_ptr<SynthEngineListView> synthEngineListView;

    juce::String engineTabName = "ENGINE";
    juce::String adsrTabName = "ADSR";
    juce::String effectTabName = "EFFECT";
    juce::String lfoTabName = "LFO";
    juce::String listTabName = "LIST";

    void addListeners();
    void removeListeners();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthView)
};

