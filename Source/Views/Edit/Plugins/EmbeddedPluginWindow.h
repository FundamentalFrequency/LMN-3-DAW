#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include "SamplerView.h"

//==============================================================================
class EmbeddedUIBehaviour : public tracktion_engine::UIBehaviour
{
public:
    EmbeddedUIBehaviour() = default;

    std::unique_ptr<juce::Component> createPluginWindow (tracktion_engine::PluginWindowState& pws) override
    {

        std::unique_ptr<juce::AudioProcessorEditor> editor;
        if (auto ws = dynamic_cast<tracktion_engine::Plugin::WindowState*> (&pws))
        {

            if (auto externalPlugin = dynamic_cast<tracktion_engine::ExternalPlugin*> (&(ws->plugin)))
            {

                if (auto pi = externalPlugin->getAudioPluginInstance())
                {
                    editor.reset(pi->createEditorIfNeeded());

                    if (editor == nullptr)
                    {
                        DBG("using generic editor");
                        editor = std::make_unique<juce::GenericAudioProcessorEditor> (*pi);
                    }

                    editor->setWantsKeyboardFocus(false);
                    return editor;
                }

            }

            if (auto samplerPlugin = dynamic_cast<tracktion_engine::SamplerPlugin*> (&(ws->plugin)))
            {

                std::unique_ptr<SamplerView> samplerView = std::make_unique<SamplerView>(samplerPlugin);
                return samplerView;

            }

        }

        DBG("failed to create editor");
        return {};
    }

};