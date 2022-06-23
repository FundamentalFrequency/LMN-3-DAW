#pragma once
#include "App.h"
#include "FourOscView.h"
#include "InternalPluginView.h"
#include "LowPassPluginView.h"
#include "SamplerView.h"
#include <app_services/app_services.h>
#include <internal_plugins/internal_plugins.h>
#include <tracktion_engine/tracktion_engine.h>

//==============================================================================
class ExtendedUIBehaviour : public tracktion::UIBehaviour {
  public:
    ExtendedUIBehaviour() = default;

    std::unique_ptr<juce::Component>
    createPluginWindow(tracktion::PluginWindowState &pws) override {
        std::unique_ptr<juce::AudioProcessorEditor> editor;
        if (auto ws =
                dynamic_cast<tracktion::Plugin::WindowState *>(&pws)) {
            if (auto externalPlugin =
                    dynamic_cast<tracktion::ExternalPlugin *>(
                        &(ws->plugin))) {
                if (auto pi = externalPlugin->getAudioPluginInstance()) {
                    editor.reset(pi->createEditorIfNeeded());

                    if (editor == nullptr) {
                        juce::Logger::writeToLog("using generic editor");
                        editor =
                            std::make_unique<juce::GenericAudioProcessorEditor>(
                                *pi);
                    }

                    editor->setWantsKeyboardFocus(false);
                    return editor;
                }
            }

            if (auto samplerPlugin =
                    dynamic_cast<tracktion::SamplerPlugin *>(
                        &(ws->plugin))) {
                if (auto drumSamplerPlugin =
                        dynamic_cast<internal_plugins::DrumSamplerPlugin *>(
                            samplerPlugin)) {
                    std::unique_ptr<SamplerView> drumSamplerView =
                        std::make_unique<SamplerView>(drumSamplerPlugin,
                                                      *midiCommandManager);

                    return drumSamplerView;

                } else {
                    std::unique_ptr<SamplerView> synthSamplerView =
                        std::make_unique<SamplerView>(samplerPlugin,
                                                      *midiCommandManager);
                    return synthSamplerView;
                }
            }

            if (auto reverbPlugin =
                    dynamic_cast<tracktion::ReverbPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(reverbPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto delayPlugin =
                    dynamic_cast<tracktion::DelayPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(delayPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto lowPassPlugin =
                    dynamic_cast<tracktion::LowPassPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<LowPassPluginView> lowPassPluginView =
                    std::make_unique<LowPassPluginView>(lowPassPlugin,
                                                        *midiCommandManager);
                return lowPassPluginView;
            }

            if (auto phaserPlugin =
                    dynamic_cast<tracktion::PhaserPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(phaserPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto chorusPlugin =
                    dynamic_cast<tracktion::ChorusPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(chorusPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto equaliserPlugin =
                    dynamic_cast<tracktion::EqualiserPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(equaliserPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto compressorPlugin =
                    dynamic_cast<tracktion::CompressorPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<InternalPluginView> internalPluginView =
                    std::make_unique<InternalPluginView>(compressorPlugin,
                                                         *midiCommandManager);
                return internalPluginView;
            }

            if (auto fourOscPlugin =
                    dynamic_cast<tracktion::FourOscPlugin *>(
                        &(ws->plugin))) {
                std::unique_ptr<FourOscView> fourOscView =
                    std::make_unique<FourOscView>(fourOscPlugin,
                                                  *midiCommandManager);
                return fourOscView;
            }

            std::unique_ptr<InternalPluginView> internalPluginView =
                std::make_unique<InternalPluginView>(&ws->plugin,
                                                     *midiCommandManager);
            return internalPluginView;
        }

        juce::Logger::writeToLog("failed to create editor");
        return {};
    }

    void setEdit(tracktion::Edit *e) { edit = e; }

    void setMidiCommandManager(app_services::MidiCommandManager *mcm) {
        midiCommandManager = mcm;
    }

    void setApp(App *a) { app = a; }

    tracktion::Edit *getCurrentlyFocusedEdit() override { return edit; }

    void runTaskWithProgressBar(
        tracktion::ThreadPoolJobWithProgress &t) override {
        TaskRunner runner(t);
        if (app != nullptr) {
            app->showProgressView();
        }

        while (runner.isThreadRunning()) {
            if (!juce::MessageManager::getInstance()->runDispatchLoopUntil(
                    10)) {
                // Can update the GUI here if we need to, but since its just a
                // continuous loading animation we dont need to do anything for
                // now
            }
        }

        // Once the thread finishes, hide the progress view
        app->hideProgressView();
    }

  private:
    tracktion::Edit *edit;
    app_services::MidiCommandManager *midiCommandManager;
    App *app;

    struct TaskRunner : public juce::Thread {
        explicit TaskRunner(tracktion::ThreadPoolJobWithProgress &t)
            : Thread(t.getJobName()), task(t) {
            startThread();
        }

        ~TaskRunner() override {
            task.signalJobShouldExit();
            waitForThreadToExit(10000);
        }

        void run() override {
            while (!threadShouldExit())
                if (task.runJob() == juce::ThreadPoolJob::jobHasFinished)
                    break;
        }

        tracktion::ThreadPoolJobWithProgress &task;
    };
};