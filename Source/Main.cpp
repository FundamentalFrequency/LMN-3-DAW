#include "Views/App/App.h"
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include "EmbeddedPluginWindow.h"
#include <SynthSampleData.h>
#include <DrumSampleData.h>

class GuiAppApplication  : public juce::JUCEApplication
{
public:

    GuiAppApplication() {}


    const juce::String getApplicationName() override       { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override    { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        juce::ignoreUnused (commandLine);

        state = app_models::StateBuilder::createInitialStateTree();
        DBG(state.toXmlString());

        initSamples();

        mainWindow.reset (new MainWindow(getApplicationName(), engine, *edit, state));
    }

    void initSamples()
    {

        // This loops through the sample binary data files
        // and adds them to the edit's temp directory
        juce::Array<juce::File> files;
        const auto destDir = edit->getTempDirectory(true);
        jassert(destDir != File());


        for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i)
        {
            const auto f = destDir.getChildFile(SynthSampleData::originalFilenames[i]);

            int dataSizeInBytes = 0;
            const char* data =  SynthSampleData::getNamedResource(SynthSampleData::namedResourceList[i], dataSizeInBytes);
            jassert (data != nullptr);
            f.replaceWithData (data, dataSizeInBytes);
            files.add(f);
        }

        for (int i = 0; i < DrumSampleData::namedResourceListSize; ++i)
        {
            const auto f = destDir.getChildFile(DrumSampleData::originalFilenames[i]);

            int dataSizeInBytes = 0;
            const char* data =  DrumSampleData::getNamedResource(DrumSampleData::namedResourceList[i], dataSizeInBytes);
            jassert (data != nullptr);
            f.replaceWithData (data, dataSizeInBytes);
            files.add(f);
        }


    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
        juce::ignoreUnused (commandLine);
    }

    class MainWindow    : public juce::DocumentWindow
    {
    public:
        explicit MainWindow (juce::String name, tracktion_engine::Engine& e, tracktion_engine::Edit& ed, juce::ValueTree v)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons),
              engine(e),
              edit(ed),
              state(v)
        {

            if (auto uiBehavior = dynamic_cast<EmbeddedUIBehaviour*>(&engine.getEngineBehaviour()))
                uiBehavior->setEdit(&edit);

            setUsingNativeTitleBar (true);
            setContentOwned (new App(edit, state), true);


           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        tracktion_engine::Engine& engine;
        tracktion_engine::Edit& edit;
        juce::ValueTree state;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    tracktion_engine::Engine engine { getApplicationName(), std::make_unique<EmbeddedUIBehaviour>(), nullptr };
    std::unique_ptr<tracktion_engine::Edit> edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
    juce::ValueTree state;

};

START_JUCE_APPLICATION (GuiAppApplication)
