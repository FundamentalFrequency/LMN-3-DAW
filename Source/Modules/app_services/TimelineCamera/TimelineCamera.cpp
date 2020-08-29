#include "TimelineCamera.h"

namespace app_services {

    TimelineCamera::TimelineCamera(double scopeAmount)
            : scope(scopeAmount) {
    }

    void TimelineCamera::setScope(double s) {

        scope = s;

    }

    void TimelineCamera::setNudgeAmount(double nudge) {

        nudgeAmount = nudge;
    }

    void TimelineCamera::setCenter(double c) {

        center = c;

    }

    void TimelineCamera::setCenterOffsetLimit(double col) {

        centerOffsetLimit = col;
    }

    double TimelineCamera::getScope() {

        return scope;
    }

    double TimelineCamera::getNudgeAmount() {

        return nudgeAmount;

    }

    double TimelineCamera::getCenter() {

        return center;

    }

    double TimelineCamera::getCenterOffsetLimit() {

        return centerOffsetLimit;

    }

    void TimelineCamera::nudgeCameraForward() {

        center += nudgeAmount;

    }

    void TimelineCamera::nudgeCameraBackward() {

        center -= nudgeAmount;

    }

    double TimelineCamera::timeRelativeToCenter(double t) {

        return t - center;

    }

    double TimelineCamera::centerRelativeTimeToX(double timeRelativeToCenter, juce::Component *component) {

        double pixelsPerSecond = component->getWidth() / scope;
        return (timeRelativeToCenter * pixelsPerSecond) + (component->getWidth() / 2.0);


    }

    double TimelineCamera::timeToX(double t, juce::Component *component) {

        return centerRelativeTimeToX(timeRelativeToCenter(t), component);

    }

}