#include "TracksView.h"

TracksView::TracksView(juce::ApplicationCommandManager& cm)
    : commandManager(cm)

{

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText("TRACKS", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);

    // Since this is the initial view, we need it to grab keyboard focus manually
    juce::Timer::callAfterDelay (300, [this] { grabKeyboardFocus(); });
    commandManager.registerAllCommandsForTarget(this);
    getTopLevelComponent()->addKeyListener(commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

}

void TracksView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void TracksView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);

}

juce::ApplicationCommandTarget* TracksView::getNextCommandTarget()
{

    return findFirstTargetParentComponent();
}

void TracksView::getAllCommands(juce::Array<juce::CommandID>& commands)
{

}

void TracksView::getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{



}

bool TracksView::perform (const InvocationInfo &info)
{

    return true;

}
