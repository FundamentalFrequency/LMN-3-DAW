#include "PluginView.h"

PluginView::PluginView()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setText(juce::CharPointer_UTF8 ("some plugin \xe2\x99\xab"), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

}

void PluginView::paint(juce::Graphics&)
{


}

void PluginView::resized()
{
    setBounds(getLocalBounds());
    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);
}

juce::ApplicationCommandTarget* PluginView::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void PluginView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}
void PluginView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{

}

bool PluginView::perform (const InvocationInfo &info)
{
    return true;
}
