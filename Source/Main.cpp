#include <ImageData.h>
#include <app_services/app_services.h>
#include <internal_plugins/internal_plugins.h>
#include <memory>
#include <tracktion_engine/tracktion_engine.h>
// #include <SynthSampleData.h>
// #include <DrumSampleData.h>

#include "ExtendedUIBehaviour.h"
#include "Views/App/MainWindowHost/MainWindowHost.h"

class LMNEngineBehaviour : public tracktion::EngineBehaviour {
  public:
    bool autoInitialiseDeviceManager() override { return false; }
};

struct EngineWrapper {
    EngineWrapper(const juce::String appName, bool recordAudioPermissionGranted)
        : recordAudioPermission(recordAudioPermissionGranted),
          engine(appName, std::make_unique<ExtendedUIBehaviour>(),
                 std::make_unique<LMNEngineBehaviour>()),
          edit(nullptr) {
        JUCE_ASSERT_MESSAGE_THREAD
        initAudioManager();
        initMcm();
    }

    ~EngineWrapper() {
        bool success = edit->engine.getTemporaryFileManager()
                           .getTempDirectory()
                           .deleteRecursively();
        if (!success) {
            juce::Logger::writeToLog("failed to clean up temporary directory " +
                                     edit->engine.getTemporaryFileManager()
                                         .getTempDirectory()
                                         .getFullPathName());
        }
    }

    void initAudioManager() {
        auto &tractionDM = engine.getDeviceManager();
        tractionDM.initialise(recordAudioPermission ? 2 : 0, 2);
    }

    void initMcm() {
        midiCommandManager =
            std::make_unique<app_services::MidiCommandManager>(engine);
    }

    void setEdit(tracktion::Edit *e) {
        edit = e;
        midiCommandManager->setEdit(edit);
    }

    tracktion::Engine engine;
    std::unique_ptr<app_services::MidiCommandManager> midiCommandManager;
    tracktion::Edit *edit;
    bool recordAudioPermission;
};

class GuiAppApplication : public juce::JUCEApplication {
  public:
    GuiAppApplication()
#if !(JUCE_IOS || JUCE_ANDROID)
        : splash(new juce::SplashScreen(
              "Welcome to my app!",
              juce::ImageFileFormat::loadFrom(
                  ImageData::tracktion_engine_powered_png,
                  ImageData::tracktion_engine_powered_pngSize),
              true))
#endif
    {
    }

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
        initLogger();

        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                          [&](bool granted) {
                                              callFunctionOnMessageThread([&] {
                                                  internalInitialise(granted);
                                              });
                                          });

#if !(JUCE_IOS || JUCE_ANDROID)
        splash->deleteAfterDelay(juce::RelativeTime::seconds(4.25), false);
#endif
    }

    void internalInitialise(bool permissionGranted) {
        engineWrapper = std::make_unique<EngineWrapper>(getApplicationName(),
                                                        permissionGranted);
        initBuiltInPlugins();

        initialiseEdit();

        if (auto uiBehavior = dynamic_cast<ExtendedUIBehaviour *>(
                &engineWrapper->engine.getUIBehaviour())) {
            uiBehavior->setEdit(edit.get());
            uiBehavior->setMidiCommandManager(
                engineWrapper->midiCommandManager.get());

            mainWindow = std::make_unique<MainWindowHost>(
                getApplicationName(), engineWrapper->engine, *edit,
                *engineWrapper->midiCommandManager);
        }

        engineWrapper->setEdit(edit.get());
    }

    void initialiseEdit() {
        // try and find an existing edit track
        auto userAppDataDirectory = juce::File::getSpecialLocation(
            juce::File::userApplicationDataDirectory);
        juce::File editFile =
            userAppDataDirectory.getChildFile(getApplicationName())
                .getChildFile("edit");
        if (editFile.existsAsFile()) {
            edit = tracktion::loadEditFromFile(engineWrapper->engine, editFile);
        } else {
            editFile.create();
            edit = tracktion::createEmptyEdit(engineWrapper->engine, editFile);
            edit->ensureNumberOfAudioTracks(8);

            for (auto track : tracktion::getAudioTracks(*edit))
                track->setColour(appLookAndFeel.getRandomColour());
        }

        ConfigurationHelpers::initSamples(engineWrapper->engine);

        // The master track does not have the default  plugins added to it by
        // default
        for (auto track : tracktion::getTopLevelTracks(*edit)) {
            if (track->isMasterTrack()) {
                if (track->pluginList
                        .getPluginsOfType<tracktion::VolumeAndPanPlugin>()
                        .getLast() == nullptr) {
                    track->pluginList.addDefaultTrackPlugins(false);
                }
            }
        }

        edit->getTransport().ensureContextAllocated();

        edit->clickTrackEnabled.setValue(true, nullptr);
        edit->setCountInMode(tracktion::Edit::CountIn::oneBar);
    }

    void shutdown() override {
        // Add your application's shutdown code here..
        mainWindow = nullptr; // (deletes our window)
        engineWrapper = nullptr;
        juce::Logger::setCurrentLogger(nullptr);
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

    template <typename Function>
    void callFunctionOnMessageThread(Function &&func) {
        if (juce::MessageManager::getInstance()->isThisTheMessageThread()) {
            func();
        } else {
            jassert(!juce::MessageManager::getInstance()
                         ->currentThreadHasLockedMessageManager());
            juce::MessageManager::callAsync([&] { func(); });
        }
    }

    void initLogger() {
        // Create application wide file logger
        logger = std::unique_ptr<juce::FileLogger>(
            juce::FileLogger::createDefaultAppLogger(
                getApplicationName(), "log.txt",
                getApplicationName() + " Logs"));
        juce::Logger::setCurrentLogger(logger.get());
    }

    void initBuiltInPlugins() {
        // we need to add the app internal plugins to the cache:
        engineWrapper->engine.getPluginManager()
            .createBuiltInType<internal_plugins::DrumSamplerPlugin>();
    }

  private:
    std::unique_ptr<juce::FileLogger> logger;
    std::unique_ptr<EngineWrapper> engineWrapper;
    std::unique_ptr<tracktion::Edit> edit;
    std::unique_ptr<MainWindowHost> mainWindow;
    AppLookAndFeel appLookAndFeel;

#if !(JUCE_ANDROID || JUCE_IOS)
    juce::SplashScreen *splash;
#endif
};

START_JUCE_APPLICATION(GuiAppApplication)
