#pragma once
#include <tracktion_engine/tracktion_engine.h>

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

        }

        DBG("failed to create editor");
        return {};
    }

};