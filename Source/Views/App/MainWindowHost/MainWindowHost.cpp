#include "MainWindowHost.h"
#include "App.h"
#include "ExtendedUIBehaviour.h"

MainWindowHost::MainWindowHost(juce::String name, tracktion::Engine &en,
                               tracktion::Edit &ed,
                               app_services::MidiCommandManager &mcm)
    : engine(en), edit(ed),
      DocumentWindow(
          name,
          juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
              ResizableWindow::backgroundColourId),
          DocumentWindow::allButtons) {
    auto userAppDataDirectory = juce::File::getSpecialLocation(
        juce::File::userApplicationDataDirectory);
    auto configFile =
        userAppDataDirectory.getChildFile(name).getChildFile("config.yaml");
    if (ConfigurationHelpers::getShowTitleBar(configFile))
        setUsingNativeTitleBar(true);
    else {
        setUsingNativeTitleBar(false);
        setTitleBarHeight(0);
    }

    setContentOwned(new App(edit, mcm), true);

#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(false, false);
    centreWithSize(getWidth(), getHeight());
#endif
    // UIBehavior is used to show progress view
    if (auto uiBehavior =
            dynamic_cast<ExtendedUIBehaviour *>(&engine.getUIBehaviour())) {
        if (auto app = dynamic_cast<App *>(getContentComponent())) {
            uiBehavior->setApp(app);
        }
    }
    setVisible(true);
}

void MainWindowHost::closeButtonPressed() {
    // This is called when the user tries to close this window. Here,
    // we'll just ask the app to quit when this happens, but you can
    // change this to do whatever you need.
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}