#include "Views/App/App.h"
#include <tracktion_engine/tracktion_engine.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>
#include <internal_plugins/internal_plugins.h>
#include "EmbeddedPluginWindow.h"
#include <SynthSampleData.h>
#include <DrumSampleData.h>
#include "AppLookAndFeel.h"
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

        // we need to add the app internal plugins to the cache:
        engine.getPluginManager().createBuiltInType<internal_plugins::DrumSamplerPlugin>();

        juce::File::SpecialLocationType documents = juce::File::SpecialLocationType::userDocumentsDirectory;
        juce::File editFile = juce::File(juce::File::getSpecialLocation(documents).getChildFile("edit"));
        if (editFile.existsAsFile())
        {

            edit = tracktion_engine::loadEditFromFile(engine, editFile);

        }
        else
        {

            editFile.create();
            edit = tracktion_engine::createEmptyEdit(engine, editFile);
            edit->ensureNumberOfAudioTracks(8);

            for (auto track : tracktion_engine::getAudioTracks(*edit))
                track->setColour(appLookAndFeel.getRandomColour());

        }


        edit->getTransport().ensureContextAllocated();
        state = app_models::StateBuilder::createInitialStateTree();
        DBG(state.toXmlString());

        initSamples();

        edit->clickTrackEnabled.setValue(true, nullptr);
        edit->setCountInMode(tracktion_engine::Edit::CountIn::oneBar);

        midiCommandManager = std::make_unique<app_services::MidiCommandManager>(engine);

        if (auto uiBehavior = dynamic_cast<EmbeddedUIBehaviour*>(&engine.getUIBehaviour()))
        {

            uiBehavior->setEdit(edit.get());
            uiBehavior->setMidiCommandManager(midiCommandManager.get());

        }

        mainWindow.reset (new MainWindow(getApplicationName(), engine, *edit, *midiCommandManager, state));
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

        edit->engine.getTemporaryFileManager().getTempDirectory().deleteRecursively();

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
        explicit MainWindow (juce::String name, tracktion_engine::Engine& e, tracktion_engine::Edit& ed,
                             app_services::MidiCommandManager& mcm, juce::ValueTree v)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons),
              engine(e),
              edit(ed),
              midiCommandManager(mcm),
              state(v)
        {




            setUsingNativeTitleBar (true);
            setContentOwned (new App(edit, midiCommandManager, state), true);


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
        app_services::MidiCommandManager& midiCommandManager;
        juce::ValueTree state;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    tracktion_engine::Engine engine { getApplicationName(), std::make_unique<EmbeddedUIBehaviour>(), nullptr };
    std::unique_ptr<tracktion_engine::Edit> edit;
    std::unique_ptr<app_services::MidiCommandManager> midiCommandManager;
    juce::ValueTree state;
    AppLookAndFeel appLookAndFeel;

};

START_JUCE_APPLICATION (GuiAppApplication)
