#include "PluginView.h"

PluginView::PluginView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

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

    deleteContentComponent();
    contentComponent = newComponent;
    if (contentComponent != nullptr)
    {
        contentComponent->setWantsKeyboardFocus(false);
        contentComponent->setBounds(getLocalBounds());
        addAndMakeVisible(contentComponent);

    }

}

void PluginView::deleteContentComponent()
{

    if (contentComponent != nullptr)
    {

        // This sets the content comp to a null pointer before deleting the old one, in case
        // anything tries to use the old one while it's in mid-deletion..
        std::unique_ptr<Component> oldCompDeleter(contentComponent.get());
        contentComponent = nullptr;

    }
}
