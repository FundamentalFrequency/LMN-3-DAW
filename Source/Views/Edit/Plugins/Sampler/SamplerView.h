#pragma once
#include "AppLookAndFeel.h"
#include "ThumbnailComponent.h"
#include "ThumbnailMarkerComponent.h"
#include "TitledListView.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <internal_plugins/internal_plugins.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>

class SamplerView : public juce::Component,
                    public app_view_models::SynthSamplerViewModel::Listener,
                    public app_services::MidiCommandManager::Listener {
  public:
    enum class SamplerType {

        SYNTH = 0,
        DRUM
    };

    SamplerView(tracktion::SamplerPlugin *sampler,
                app_services::MidiCommandManager &mcm);
    SamplerView(internal_plugins::DrumSamplerPlugin *drumSampler,
                app_services::MidiCommandManager &mcm);
    ~SamplerView() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void sampleChanged() override;
    void sampleExcerptTimesChanged() override;
    void fullSampleThumbnailChanged() override;
    void sampleExcerptThumbnailChanged() override;
    void gainChanged() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder2Increased() override;
    void encoder2Decreased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void encoder4Increased() override;
    void encoder4Decreased() override;

    void controlButtonPressed() override;
    void controlButtonReleased() override;

    void noteOnPressed(int noteNumber) override;

  private:
    void init();

  protected:
    tracktion::SamplerPlugin *samplerPlugin;
    app_services::MidiCommandManager &midiCommandManager;
    std::unique_ptr<app_view_models::SamplerViewModel> viewModel;
    AppLookAndFeel appLookAndFeel;
    ThumbnailComponent fullSampleThumbnail;
    ThumbnailComponent sampleExcerptThumbnail;
    juce::DrawableRectangle startMarker;
    juce::DrawableRectangle endMarker;
    TitledListView titledList;
    juce::Label sampleLabel;
    juce::Label gainLabel;
    juce::Label emptyLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplerView)
};
