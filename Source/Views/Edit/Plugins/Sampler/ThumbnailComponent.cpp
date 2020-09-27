#include "ThumbnailComponent.h"

ThumbnailComponent::ThumbnailComponent(juce::AudioThumbnail& thumb, juce::Colour c)
    : thumbnail(thumb),
      colour(c)
{

    thumbnail.addChangeListener(this);
}

ThumbnailComponent::~ThumbnailComponent()
{

    thumbnail.removeChangeListener(this);
}

void ThumbnailComponent::paint(juce::Graphics &g)
{

    g.setColour(colour);

    if (thumbnail.getNumChannels() > 0)
        thumbnail.drawChannels(g, getLocalArea(getParentComponent(), paintBounds), 0, thumbnail.getTotalLength(), 1.0f);



}

void ThumbnailComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{

    if (source == &thumbnail)
        repaint();

}

void ThumbnailComponent::setPaintBounds(juce::Rectangle<int> bounds)
{

    paintBounds = bounds;

}