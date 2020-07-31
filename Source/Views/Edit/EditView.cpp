#include "EditView.h"
EditView::EditView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
    // Since this is the initial view, we need it to grab keyboard focus manually
    // this should already have it since its done in the app tab changed callback
    // but just to be safe
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });
    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText("EDIT", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);

}

void EditView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void EditView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);

}

juce::ApplicationCommandTarget* EditView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void EditView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void EditView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool EditView::perform (const InvocationInfo &info)
{

    return true;

}
