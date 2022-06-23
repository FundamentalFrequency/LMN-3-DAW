#include "PluginView.h"

PluginView::PluginView(app_services::MidiCommandManager &mcm,
                       tracktion::Plugin::Ptr p, Component *pluginComp)
    : midiCommandManager(mcm), plugin(p), pluginComponent(pluginComp) {
    midiCommandManager.addListener(this);

    if (pluginComponent != nullptr) {
        addAndMakeVisible(pluginComponent);
    }
}

PluginView::~PluginView() {
    midiCommandManager.removeListener(this);
    if (plugin != nullptr) {
        plugin->windowState->closeWindowExplicitly();
    }
}
void PluginView::paint(juce::Graphics &) {}

void PluginView::resized() {
    if (pluginComponent != nullptr) {
        pluginComponent->setBounds(getLocalBounds());
    }
}

tracktion::Plugin::Ptr PluginView::getPlugin() { return plugin; }
