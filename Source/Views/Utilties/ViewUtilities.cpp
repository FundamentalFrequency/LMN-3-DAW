#include "ViewUtilities.h"

namespace ViewUtilities
{

    double timeRelativeToTransport(double t, double transportTime)
    {

        return t - transportTime;

    }

    double timeRelativeToTransportToX(double timeRelativeToTransport, juce::Component* trackComponent)
    {

        return (timeRelativeToTransport * pixelsPerSecond) + (trackComponent->getWidth() / 2.0);

    }

    double timeToX(double t, double transportTime, juce::Component* trackComponent)
    {

        return timeRelativeToTransportToX(timeRelativeToTransport(t, transportTime), trackComponent);

    }


}