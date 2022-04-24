#include "EngineHelpers.h"

namespace app_view_models {

    bool EngineHelpers::isTrackArmed(tracktion_engine::AudioTrack &t, int position) {
        auto &edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack(t, position))
                return instance->isRecordingEnabled(t);

        return false;
    }

    juce::Array<tracktion_engine::Track*> EngineHelpers::getAudioAndMasterTracks(tracktion_engine::Edit& e) {
        juce::Array<tracktion_engine::Track*> tracks;
        tracks.ensureStorageAllocated (32);
        for (auto track : tracktion_engine::getTopLevelTracks(e)) {
            if (track->isAudioTrack() || track->isMasterTrack()) {
                tracks.add(track);
            }
        }

        return tracks;
    }

    tracktion_engine::VolumeAndPanPlugin* EngineHelpers::getVolumeAndPanPluginForTrack(tracktion_engine::Track* track) {
        if (track->isMasterTrack()) {
            return track->edit.getMasterVolumePlugin();
        }

        return track->pluginList.getPluginsOfType<tracktion_engine::VolumeAndPanPlugin>().getLast();
    }

    template<typename ClipType>
    typename ClipType::Ptr loopAroundClip (ClipType& clip) {
        auto& transport = clip.edit.getTransport();
        transport.setLoopRange(clip.getEditTimeRange());
        transport.looping = true;
        return clip;
    }
}