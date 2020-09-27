#pragma  once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>
#include "TitledListView.h"
#include "AppLookAndFeel.h"
#include "ThumbnailComponent.h"
#include "ThumbnailMarkerComponent.h"
class SamplerView
    : public juce::Component,
      public app_view_models::SamplerViewModel::Listener,
      public app_services::MidiCommandManager::Listener
{

public:

    SamplerView(tracktion_engine::SamplerPlugin* sampler, app_services::MidiCommandManager& mcm);
    ~SamplerView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void sampleChanged() override;
    void sampleExcerptTimesChanged() override;
    void fullSampleThumbnailChanged() override;
    void sampleExcerptThumbnailChanged() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonPressed() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

private:

    tracktion_engine::SamplerPlugin* samplerPlugin;
    app_services::MidiCommandManager& midiCommandManager;
    app_view_models::SamplerViewModel viewModel;
    AppLookAndFeel appLookAndFeel;
    ThumbnailComponent fullSampleThumbnail;
    ThumbnailComponent sampleExcerptThumbnail;
    juce::DrawableRectangle startMarker;
    juce::DrawableRectangle endMarker;
    TitledListView titledList;
    juce::Label sampleLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplerView);

};



