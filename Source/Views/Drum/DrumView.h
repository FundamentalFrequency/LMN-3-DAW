#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_models/app_models.h>
#include <memory>
#include "DrumEngineParametersView.h"
#include "ADSRParametersView.h"
#include "EffectParametersView.h"
#include "LFOParametersView.h"
#include "Views/List/Engine/Drum/DrumEngineListView.h"

class DrumView : public juce::TabbedComponent,
                 public juce::ApplicationCommandTarget
{
public:
    DrumView(app_models::PresetSlots& ps);
    ~DrumView();

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

private:
    app_models::PresetSlots& presetSlots;

    std::unique_ptr<DrumEngineParametersView> drumEngineParametersView;
    std::unique_ptr<ADSRParametersView> adsrParametersView;
    std::unique_ptr<EffectParametersView> effectParametersView;
    std::unique_ptr<LFOParametersView> lfoParametersView;
    std::unique_ptr<DrumEngineListView> drumEngineListView;

    juce::String engineTabName = "ENGINE";
    juce::String adsrTabName = "ADSR";
    juce::String effectTabName = "EFFECT";
    juce::String lfoTabName = "LFO";
    juce::String listTabName = "LIST";

    juce::ApplicationCommandManager commandManager;

    void addListeners();
    void removeListeners();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumView)
};

