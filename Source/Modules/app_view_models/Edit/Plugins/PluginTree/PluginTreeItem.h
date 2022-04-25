#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include "PluginTreeBase.h"

namespace app_view_models {

    static inline const char *getInternalPluginFormatName() { return "TracktionInternal"; }

    class PluginTreeItem : public PluginTreeBase {
    public:
        PluginTreeItem(const juce::PluginDescription &desc);

        PluginTreeItem(const juce::String &uniqueId, const juce::String &name, const juce::String &xmlType,
                       bool isSynth, bool isPlugin);

        tracktion_engine::Plugin::Ptr create(tracktion_engine::Edit &edit);

        juce::String getUniqueName() const override;

        juce::PluginDescription description;
        juce::String xmlType;
        bool isPlugin = true;

    private:
        JUCE_LEAK_DETECTOR(PluginTreeItem)

    };

}


