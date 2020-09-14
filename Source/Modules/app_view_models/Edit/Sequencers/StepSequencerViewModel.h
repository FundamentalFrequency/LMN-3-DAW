#pragma once

namespace app_view_models
{

    class StepSequencerViewModel
    {
    public:

        StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t);
        ~StepSequencerViewModel();

        int getNumChannels();
        int getNumNotesPerChannel();

    private:
        tracktion_engine::AudioTrack::Ptr track;
        tracktion_engine::StepClip::Ptr stepClip;

    };

}

