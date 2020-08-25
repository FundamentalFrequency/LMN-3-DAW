#include "RecordingClipComponent.h"
#include "ViewUtilities.h"
RecordingClipComponent::RecordingClipComponent(tracktion_engine::Track::Ptr t)
: track(t)
{

    startTimerHz(120);

}

void RecordingClipComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::red.withAlpha(0.5f));
    g.setColour(juce::Colours::black);
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

        // 7 seconds can be show on the track view
//        double viewStartTime = 0.0;
//        double viewEndTime = 7.0;
//        t1 = juce::jmax(t1, viewStartTime);
//        t2 = juce::jmin(t2, viewEndTime);

        if (auto p = getParentComponent())
        {


            int x1 = ceil(ViewUtilities::timeToX(t1, edit.getTransport().getCurrentPosition(), p));

            setBounds(x1, 0, (p->getWidth() / 2.0) - x1, p->getHeight());
            return;

        }

    }

    setBounds({});



}

