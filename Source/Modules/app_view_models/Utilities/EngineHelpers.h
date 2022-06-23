#pragma once
namespace app_view_models::EngineHelpers {
bool isTrackArmed(tracktion::AudioTrack &t, int position = 0);
juce::Array<tracktion::Track *> getAudioAndMasterTracks(tracktion::Edit &e);
tracktion::VolumeAndPanPlugin *
getVolumeAndPanPluginForTrack(tracktion::Track *track);
} // namespace app_view_models::EngineHelpers
