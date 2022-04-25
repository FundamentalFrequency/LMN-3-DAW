#include "ProgressView.h"

ProgressView::ProgressView() {
    addAndMakeVisible(svgImageComponent);
    startTimerHz(refreshRate);
}

void ProgressView::resized() {
    // For some reason setting the bounds of the drawable to be rotated was not working
    // It seemed to ignore the transform or something.
    // I decided to wrap the drawable in this component svgImageComponent and then apply the rotation
    // to the component instead of to the drawable directly :/
    double speed = 2.5;
    auto angle = speed * juce::MathConstants<float>::pi / refreshRate;
    setRotatedWithBounds(svgImageComponent, float(angle), true, getLocalBounds().reduced(4));
}

void ProgressView::timerCallback() {
    resized();
}

void ProgressView::setRotatedWithBounds(Component& component, float angle, bool clockWiseRotation, juce::Rectangle<int> bounds) {
    if (! clockWiseRotation) {
        angle *= -1.0f;
    }
    component.setSize(bounds.getHeight(), bounds.getWidth());
    component.setCentrePosition(0, 0);
    component.setTransform (component.getTransform().rotated(angle).translated (float(bounds.getCentreX()), float(bounds.getCentreY())));
}



