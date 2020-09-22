#include "RecordingClipComponent.h"

RecordingClipComponent::RecordingClipComponent(tracktion_engine::Track::Ptr t, app_services::TimelineCamera& cam)
    : track(t),
      camera(cam)
{

    startTimerHz(120);

}

void RecordingClipComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::red.withAlpha(0.5f));
    g.setColour(appLookAndFeel.colour3);
    g.drawRect(getLocalBounds());

}

void RecordingClipComponent::timerCallback()
{

    updatePosition();

}
void RecordingClipComponent::updatePosition()
{

    auto& edit = track->edit;

    if (auto playhead = edit.getTransport().getCurrentPlayhead())
    {

        double t1 = punchInTime >= 0 ? punchInTime : edit.getTransport().getTimeWhenStarted();
        double t2 = juce::jmax(t1, playhead->getUnloopedPosition());

        if (playhead->isLooping())
        {
            auto loopTimes = playhead->getLoopTimes();

            if (t2 >= loopTimes.end)
            {
                t1 = juce::jmin(t1, loopTimes.start);
                t2 = loopTimes.end;
            }
        }
        else if (edit.recordingPunchInOut)
        {
            auto mr = edit.getTransport().getLoopRange();
            auto in  = mr.getStart();
            auto out = mr.getEnd();

            t1 = juce::jlimit (in, out, t1);
            t2 = juce::jlimit (in, out, t2);
        }

        if (auto p = getParentComponent())
        {


            int x1 = ceil(camera.timeToX(t1, p->getWidth()));
            int x2 = ceil(camera.timeToX(t2, p->getWidth()));

            setBounds(x1, 0, x2 - x1, p->getHeight());
            return;

        }

    }

    setBounds({});

}

