#include "PluginView.h"

PluginView::PluginView(app_services::MidiCommandManager& mcm, Component* plugin)
    : midiCommandManager(mcm),
      pluginComponent(plugin)
{

    midiCommandManager.addListener(this);

    if (pluginComponent != nullptr)
    {
        addAndMakeVisible(pluginComponent);

    }
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

    if (pluginComponent != nullptr)
    {
        pluginComponent->setBounds(getLocalBounds());
    }

}

