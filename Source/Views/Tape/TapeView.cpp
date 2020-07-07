#include "TapeView.h"
TapeView::TapeView()
{

    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);
    // Since this is the initial view, we need it to grab keyboard focus manually
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText("TAPE", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);

}

void TapeView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void TapeView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);

}

juce::ApplicationCommandTarget* TapeView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TapeView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void TapeView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool TapeView::perform (const InvocationInfo &info)
{

    return true;

}
