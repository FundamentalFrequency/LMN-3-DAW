#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <memory>
#include "PresetSlots.h"
#include "SynthEngineParametersView.h"
#include "ADSRParametersView.h"
#include "EffectParametersView.h"
#include "LFOParametersView.h"
#include "SynthEngineListView.h"

class SynthView : public juce::TabbedComponent,
                  public juce::ApplicationCommandTarget

{
public:
    SynthView(PresetSlots& ps);

    ~SynthView();

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo &info) override;

private:

    PresetSlots& presetSlots;
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

    juce::ApplicationCommandManager commandManager;

    void addListeners();
    void removeListeners();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthView)
};

