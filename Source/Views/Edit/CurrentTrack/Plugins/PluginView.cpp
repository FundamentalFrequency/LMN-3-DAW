#include "PluginView.h"

PluginView::PluginView(MidiCommandManager& mcm)
    : midiCommandManager(mcm)
{

    midiCommandManager.addListener(this);

}

PluginView::~PluginView()
{

    midiCommandManager.removeListener(this);

}
void PluginView::paint(juce::Graphics&)
{


}

void PluginView::resized()
{

    if (contentComponent != nullptr)
    {
        contentComponent->setBounds(getLocalBounds());
    }

}

void PluginView::setViewedComponent(Component* const newComponent)
{

    contentComponent = newComponent;
    if (contentComponent != nullptr)
    {
        contentComponent->setWantsKeyboardFocus(false);
        contentComponent->setBounds(getLocalBounds());
        addAndMakeVisible(contentComponent);
        resized();
    }
    
}



