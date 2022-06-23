#pragma once
#include "AppLookAndFeel.h"
#include "ClipComponent.h"
#include "RecordingClipComponent.h"
#include "SelectedTrackMarker.h"
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>

class TrackView : public juce::Component,
                  public app_view_models::TrackViewModel::Listener,
                  private juce::Timer {
  public:
    TrackView(tracktion::AudioTrack::Ptr t, app_services::TimelineCamera &cam);
    ~TrackView();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void setSelected(bool selected);

    void clipsChanged(const juce::Array<tracktion::Clip *> &clips) override;
    void
    clipPositionsChanged(const juce::Array<tracktion::Clip *> &clips) override;
    void transportChanged() override;

  private:
    tracktion::AudioTrack::Ptr track;
    app_services::TimelineCamera &camera;
    app_view_models::TrackViewModel viewModel;
    bool isSelected = false;

    juce::OwnedArray<ClipComponent> clips;
    std::unique_ptr<RecordingClipComponent> recordingClip;

    SelectedTrackMarker selectedTrackMarker;
    AppLookAndFeel appLookAndFeel;
    void timerCallback() override;
    void buildClips();
    void buildRecordingClip();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackView)
};
