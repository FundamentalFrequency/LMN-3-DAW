#include "SVGImageComponent.h"
#include "ImageData.h"

SVGImageComponent::SVGImageComponent() {
    auto image = juce::ImageFileFormat::loadFrom(ImageData::lemonsolid_svg,
                                                 ImageData::lemonsolid_svgSize);
    icon = juce::Drawable::createFromImageData(ImageData::lemonsolid_svg,
                                               ImageData::lemonsolid_svgSize);
    icon->replaceColour(juce::Colours::black, appLookAndFeel.yellowColour);
    addAndMakeVisible(icon.get());
}

void SVGImageComponent::resized() {
    juce::Rectangle<int> bounds = getLocalBounds();
    icon->setTransformToFit(bounds.toFloat(),
                            juce::RectanglePlacement::centred);
}
