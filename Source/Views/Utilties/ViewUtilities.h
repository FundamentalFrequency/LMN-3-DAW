#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
namespace ViewUtilities {

    double timeRelativeToTransport(double t, double transportTime);
    double timeRelativeToTransportToX(double timeRelativeToTransport, juce::Component* trackComponent, double pixelsPerSecond = 44);
    double timeToX(double t, double transportTime, juce::Component* trackComponent, double pixelsPerSecond = 44);

}
