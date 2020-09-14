#include "StepSequencerViewModel.h"

namespace app_view_models
{

    StepSequencerViewModel::StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t)
    : track(t)
    {

        // Find length of 4 bars (16 beats)
        double secondsPerBeat = 1.0 / track->edit.tempoSequence.getBeatsPerSecondAt(0.0);
        double startTime = track->edit.getTransport().getCurrentPosition();
        double endTime = startTime + 16 * secondsPerBeat;
        const tracktion_engine::EditTimeRange editTimeRange(startTime, endTime);
        stepClip = dynamic_cast<tracktion_engine::StepClip*>(track->insertNewClip(tracktion_engine::TrackItem::Type::step,
                                                                                     "Step Clip",
                                                                                     editTimeRange,
                                                                                     nullptr));

        // Default number of channels is 8, we need to have 24
        while (stepClip->getChannels().size() < 24)
        {
            stepClip->insertNewChannel(stepClip->getChannels().size());
        }

        // randomize the channels for now
        // gonna need some way to save the pattern in the future
        for (auto channel : stepClip->getChannels())
        {

            for (auto& pattern : stepClip->getPatterns())
            {

                pattern.setNumNotes(16);
                pattern.randomiseChannel(channel->getIndex());

            }

        }

        loopAroundClip(*stepClip);

    }

    StepSequencerViewModel::~StepSequencerViewModel()
    {

    }

    int StepSequencerViewModel::getNumChannels()
    {

        return stepClip->getChannels().size();

    }

    int StepSequencerViewModel::getNumNotesPerChannel()
    {

        return stepClip->getPattern(0).getNumNotes();

    }

}
