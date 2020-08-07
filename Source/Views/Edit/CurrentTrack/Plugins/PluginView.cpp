#include "PluginView.h"

PluginView::PluginView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    addKeyListener(this);
    setWantsKeyboardFocus(true);

}

PluginView::~PluginView()
{

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

    if (hasKeyboardFocus(false))
        DBG("plugin view has focus");

}

juce::ApplicationCommandTarget* PluginView::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void PluginView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}
void PluginView::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

}

bool PluginView::perform(const InvocationInfo &info)
{
    return true;
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

bool PluginView::keyPressed(const juce::KeyPress& key, Component* originatingComponent)
{
    DBG("key press detected");
    return false;
}
bool PluginView::keyStateChanged(bool isKeyDown, Component *originatingComponent)
{
    return false;
}

