#pragma once

namespace app_services {

class TimelineCamera {

  public:
    TimelineCamera(double scopeAmount);

    void setScope(double s);

    void setNudgeAmount(double nudge);

    void setCenter(double c);

    void setCenterOffsetLimit(double col);

    double getScope();

    double getNudgeAmount();

    double getCenter();

    double getCenterOffsetLimit();

    void nudgeCameraForward();

    void nudgeCameraBackward();

    double timeToX(double t, double width);

  private:
    // how much time is shown in the view
    double scope = 7;

    // how many seconds to move forward or backward
    double nudgeAmount = .2;

    // the point in time the camera is focused on currently
    // this point is the time being displayed at the center of the screen
    double center = scope / 2.0;

    // if the distance between the transport time and the center
    // exceeds this limit, we need to scroll the camera
    double centerOffsetLimit = (scope / 2.0) * .9;

    double timeRelativeToCenter(double t);

    double centerRelativeTimeToX(double timeRelativeToCenter, double width);
};

} // namespace app_services