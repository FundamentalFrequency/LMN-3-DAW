#include "EngineHelpers.h"

namespace app_view_models {

    bool EngineHelpers::isTrackArmed(tracktion_engine::AudioTrack &t, int position)
    {
        auto &edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack(t, position))
                return instance->isRecordingEnabled(t);

        return false;

    }

    template<typename ClipType>
    typename ClipType::Ptr loopAroundClip (ClipType& clip)
    {

        auto& transport = clip.edit.getTransport();
        transport.setLoopRange(clip.getEditTimeRange());
        transport.looping = true;
        return clip;

    }

}