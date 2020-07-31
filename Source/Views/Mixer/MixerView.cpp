#include "MixerView.h"

MixerView::MixerView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText("MIXER", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);

}

void MixerView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void MixerView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);

}

juce::ApplicationCommandTarget* MixerView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void MixerView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void MixerView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool MixerView::perform (const InvocationInfo &info)
{

    return true;

}
