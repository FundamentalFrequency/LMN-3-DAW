#include "App.h"
#include "ExtendedUIBehaviour.h"
#include <ImageData.h>
#include <app_models/app_models.h>
#include <app_services/app_services.h>
#include <internal_plugins/internal_plugins.h>
#include <tracktion_engine/tracktion_engine.h>
//#include <SynthSampleData.h>
//#include <DrumSampleData.h>

#include "AppLookAndFeel.h"
#include <memory>
class GuiAppApplication : public juce::JUCEApplication {
  public:
    GuiAppApplication()
        : splash(new juce::SplashScreen(
              "Welcome to my app!",
              juce::ImageFileFormat::loadFrom(
                  ImageData::tracktion_engine_powered_png,
                  ImageData::tracktion_engine_powered_pngSize),
              true)) {}

    const juce::String getApplicationName() override {
        return JUCE_APPLICATION_NAME_STRING;
    }
    const juce::String getApplicationVersion() override {
        return JUCE_APPLICATION_VERSION_STRING;
    }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String &commandLine) override {
        // This method is where you should put your application's initialisation
        // code..
        juce::ignoreUnused(commandLine);

        // Create application wide file logger
        logger = std::unique_ptr<juce::FileLogger>(
            juce::FileLogger::createDefaultAppLogger("LMN3", "log.txt",
                                                     "LMN3 Logs"));
        juce::Logger::setCurrentLogger(logger.get());

        // we need to add the app internal plugins to the cache:
        engine.getPluginManager()
            .createBuiltInType<internal_plugins::DrumSamplerPlugin>();

        juce::File::SpecialLocationType documents =
            juce::File::SpecialLocationType::userDocumentsDirectory;
        juce::File editFile = juce::File(
            juce::File::getSpecialLocation(documents).getChildFile("edit"));
        if (editFile.existsAsFile()) {
            edit = tracktion_engine::loadEditFromFile(engine, editFile);
        } else {
            editFile.create();
            edit = tracktion_engine::createEmptyEdit(engine, editFile);
            edit->ensureNumberOfAudioTracks(8);

            for (auto track : tracktion_engine::getAudioTracks(*edit))
                track->setColour(appLookAndFeel.getRandomColour());
        }

        // The master track does not have the default  plugins added to it by
        // default
        for (auto track : tracktion_engine::getTopLevelTracks(*edit)) {
            if (track->isMasterTrack()) {
                if (track->pluginList
                        .getPluginsOfType<
                            tracktion_engine::VolumeAndPanPlugin>()
                        .getLast() == nullptr) {
                    track->pluginList.addDefaultTrackPlugins(false);
                }
            }
        }

        edit->getTransport().ensureContextAllocated();
        initSamples();

        edit->clickTrackEnabled.setValue(true, nullptr);
        edit->setCountInMode(tracktion_engine::Edit::CountIn::oneBar);

        midiCommandManager =
            std::make_unique<app_services::MidiCommandManager>(engine);

        if (auto uiBehavior =
                dynamic_cast<ExtendedUIBehaviour *>(&engine.getUIBehaviour())) {
            uiBehavior->setEdit(edit.get());
            uiBehavior->setMidiCommandManager(midiCommandManager.get());
        }

        initialiseAudioDevices();

        mainWindow = std::make_unique<MainWindow>(getApplicationName(), engine,
                                                  *edit, *midiCommandManager);
        splash->deleteAfterDelay(juce::RelativeTime::seconds(4.25), false);
    }

    void initialiseAudioDevices() {
        auto &deviceManager = engine.getDeviceManager().deviceManager;
        deviceManager.getCurrentDeviceTypeObject()->scanForDevices();
        auto result = deviceManager.initialiseWithDefaultDevices(0, 2);
        if (result != "") {
            juce::Logger::writeToLog(
                "Attempt to initialise default devices failed!");
        }
    }

    static bool writeBinarySampleToDirectory(const juce::File &destDir,
                                             juce::StringRef filename,
                                             const char *data,
                                             int dataSizeInBytes) {
        auto f = destDir.getChildFile(filename);
        jassert(data != nullptr);
        return f.replaceWithData(data, dataSizeInBytes);
    }

    //    static void initBinarySamples(const juce::File &tempSynthDir,
    //                                  const juce::File &tempDrumDir) {
    //        for (int i = 0; i < SynthSampleData::namedResourceListSize; ++i) {
    //            int dataSizeInBytes = 0;
    //            const char *data = SynthSampleData::getNamedResource(
    //                SynthSampleData::namedResourceList[i], dataSizeInBytes);
    //            auto success = writeBinarySampleToDirectory(
    //                tempSynthDir, SynthSampleData::originalFilenames[i], data,
    //                dataSizeInBytes);
    //            if (!success) {
    //                juce::Logger::writeToLog(
    //                    "Attempt to write binary synth sample data file
    //                    failed!");
    //            }
    //        }
    //
    //        for (int i = 0; i < DrumSampleData::namedResourceListSize; ++i) {
    //            int dataSizeInBytes = 0;
    //            const char *data = DrumSampleData::getNamedResource(
    //                DrumSampleData::namedResourceList[i], dataSizeInBytes);
    //            auto success = writeBinarySampleToDirectory(
    //                tempDrumDir, DrumSampleData::originalFilenames[i], data,
    //                dataSizeInBytes);
    //            if (!success) {
    //                juce::Logger::writeToLog(
    //                    "Attempt to write binary drum sample data file
    //                    failed!");
    //            }
    //        }
    //    }

    void initUserSamples(const juce::File &tempSynthDir,
                         const juce::File &tempDrumDir) {
        auto userAppDataDirectory = juce::File::getSpecialLocation(
            juce::File::userApplicationDataDirectory);
        auto userSynthSampleDir =
            userAppDataDirectory.getChildFile(getApplicationName())
                .getChildFile("synth_samples");
        auto userDrumSampleDir =
            userAppDataDirectory.getChildFile(getApplicationName())
                .getChildFile("drum_kits");
        if (userSynthSampleDir.exists()) {
            auto success = userSynthSampleDir.copyDirectoryTo(tempSynthDir);
            if (!success)
                juce::Logger::writeToLog(
                    "Attempt to copy user synth sample data failed!");
        } else {
            juce::Logger::writeToLog(
                "User synth sample directory does not exist, creating it now.");
            auto result = userSynthSampleDir.createDirectory();
            if (result.failed())
                juce::Logger::writeToLog(
                    "Attempt to create user synth sample directory failed!: " +
                    result.getErrorMessage());
        }

        if (userDrumSampleDir.exists()) {
            auto success = userDrumSampleDir.copyDirectoryTo(tempDrumDir);
            if (!success)
                juce::Logger::writeToLog(
                    "Attempt to copy user drum kit data failed!");
        } else {
            juce::Logger::writeToLog(
                "User drum kit directory does not exist, creating it now.");
            auto result = userDrumSampleDir.createDirectory();
            if (result.failed())
                juce::Logger::writeToLog(
                    "Attempt to create user drum kit directory failed!: " +
                    result.getErrorMessage());
        }
    }

    // For some reason the tracktion version of this using the temp file manager
    // was not working correctly unless I created the directory first
    juce::File createTempDirectory(const juce::String &folderName) {
        auto dir = engine.getTemporaryFileManager().getTempFile(folderName);
        auto result = dir.createDirectory();
        if (!result.wasOk()) {
            juce::Logger::writeToLog("Error creating temporary directory " +
                                     folderName);
            return {};
        } else {
            return dir;
        }
    }

    void initSamples() {
        auto tempSynthSamplesDir = createTempDirectory("synth_samples");
        auto tempDrumKitsDir = createTempDirectory("drum_kits");
        //        initBinarySamples(tempSynthSamplesDir, tempDrumKitsDir);
        initUserSamples(tempSynthSamplesDir, tempDrumKitsDir);
    }

    void shutdown() override {
        // Add your application's shutdown code here..

        bool success = edit->engine.getTemporaryFileManager()
                           .getTempDirectory()
                           .deleteRecursively();
        if (!success) {
            juce::Logger::writeToLog("failed to clean up temporary directory " +
                                     edit->engine.getTemporaryFileManager()
                                         .getTempDirectory()
                                         .getFullPathName());
        }
        mainWindow = nullptr; // (deletes our window)
    }

    void systemRequestedQuit() override {
        // This is called when the app is being asked to quit: you can ignore
        // this request and let the app carry on running, or call quit() to
        // allow the app to close.
        quit();
    }

    void anotherInstanceStarted(const juce::String &commandLine) override {
        // When another instance of the app is launched while this one is
        // running, this method is invoked, and the commandLine parameter tells
        // you what the other instance's command-line arguments were.
        juce::ignoreUnused(commandLine);
    }

    class MainWindow : public juce::DocumentWindow {
      public:
        explicit MainWindow(juce::String name, tracktion_engine::Engine &e,
                            tracktion_engine::Edit &ed,
                            app_services::MidiCommandManager &mcm)
            : DocumentWindow(
                  name,
                  juce::Desktop::getInstance()
                      .getDefaultLookAndFeel()
                      .findColour(ResizableWindow::backgroundColourId),
                  DocumentWindow::allButtons),
              engine(e), edit(ed), midiCommandManager(mcm) {
            setUsingNativeTitleBar(true);
            setContentOwned(new App(edit, midiCommandManager), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
#endif
            // UIBehavior is used to show progress view
            if (auto uiBehavior = dynamic_cast<ExtendedUIBehaviour *>(
                    &engine.getUIBehaviour())) {
                if (auto app = dynamic_cast<App *>(getContentComponent())) {
                    uiBehavior->setApp(app);
                }
            }
            setVisible(true);
        }

        void closeButtonPressed() override {
            // This is called when the user tries to close this window. Here,
            // we'll just ask the app to quit when this happens, but you can
            // change this to do whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the
           base class uses a lot of them, so by overriding you might break its
           functionality. It's best to do all your work in your content
           component instead, but if you really have to override any
           DocumentWindow methods, make sure your subclass also calls the
           superclass's method.
        */

      private:
        tracktion_engine::Engine &engine;
        tracktion_engine::Edit &edit;
        app_services::MidiCommandManager &midiCommandManager;
        juce::ValueTree state;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

  private:
    std::unique_ptr<juce::FileLogger> logger;
    std::unique_ptr<MainWindow> mainWindow;
    tracktion_engine::Engine engine{
        getApplicationName(), std::make_unique<ExtendedUIBehaviour>(), nullptr};
    std::unique_ptr<tracktion_engine::Edit> edit;
    std::unique_ptr<app_services::MidiCommandManager> midiCommandManager;
    AppLookAndFeel appLookAndFeel;
    juce::SplashScreen *splash;
};

START_JUCE_APPLICATION(GuiAppApplication)
