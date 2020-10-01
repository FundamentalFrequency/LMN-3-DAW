#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <internal_plugins/internal_plugins.h>
#include <app_services/app_services.h>
#include "SamplerView.h"
//==============================================================================
class EmbeddedUIBehaviour : public tracktion_engine::UIBehaviour
{
public:
    EmbeddedUIBehaviour() = default;

    std::unique_ptr<juce::Component> createPluginWindow(tracktion_engine::PluginWindowState& pws) override
    {

        std::unique_ptr<juce::AudioProcessorEditor> editor;
        if (auto ws = dynamic_cast<tracktion_engine::Plugin::WindowState*>(&pws))
        {

            if (auto externalPlugin = dynamic_cast<tracktion_engine::ExternalPlugin*>(&(ws->plugin)))
            {

                if (auto pi = externalPlugin->getAudioPluginInstance())
                {
                    editor.reset(pi->createEditorIfNeeded());

                    if (editor == nullptr)
                    {
                        DBG("using generic editor");
                        editor = std::make_unique<juce::GenericAudioProcessorEditor>(*pi);
                    }

                    editor->setWantsKeyboardFocus(false);
                    return editor;
                }

            }

            if (auto samplerPlugin = dynamic_cast<tracktion_engine::SamplerPlugin*>(&(ws->plugin)))
            {

                if (auto drumSamplerPlugin = dynamic_cast<internal_plugins::DrumSamplerPlugin*>(samplerPlugin))
                {


                    std::unique_ptr<SamplerView> drumSamplerView = std::make_unique<SamplerView>(drumSamplerPlugin,
                                                                                                       *midiCommandManager);

                    return drumSamplerView;


                }
                else
                {
                    std::unique_ptr<SamplerView> synthSamplerView = std::make_unique<SamplerView>(samplerPlugin,
                                                                                                 *midiCommandManager);

                    return synthSamplerView;
                }


            }

        }

        DBG("failed to create editor");
        return {};
    }

    void setEdit(tracktion_engine::Edit* e) { edit = e; }

    void setMidiCommandManager(app_services::MidiCommandManager* mcm) { midiCommandManager = mcm; }

    tracktion_engine::Edit* getCurrentlyFocusedEdit() override { return edit; }


private:

    tracktion_engine::Edit* edit;
    app_services::MidiCommandManager* midiCommandManager;

};