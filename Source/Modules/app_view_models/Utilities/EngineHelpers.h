#pragma once

namespace app_view_models::EngineHelpers {
bool isTrackArmed(tracktion_engine::AudioTrack &t, int position = 0);
juce::Array<tracktion_engine::Track *>
getAudioAndMasterTracks(tracktion_engine::Edit &e);
tracktion_engine::VolumeAndPanPlugin *
getVolumeAndPanPluginForTrack(tracktion_engine::Track *track);
} // namespace app_view_models::EngineHelpers
