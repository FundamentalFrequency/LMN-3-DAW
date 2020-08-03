#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include "PluginTreeBase.h"

class PluginTreeGroup : public PluginTreeBase {

public:

    enum class PluginTreeGroupType
    {
        INSTRUMENTS,
        EFFECTS,
        MODULATORS,
        FOLDER_NAME
    };

    PluginTreeGroup (tracktion_engine::Edit& e, PluginTreeGroupType t);
    PluginTreeGroup (tracktion_engine::Edit& e, PluginTreeGroupType t, const juce::String& s);

    juce::String getUniqueName() const override;

    juce::String name;

private:

    tracktion_engine::Edit& edit;
    PluginTreeGroupType type;

    void scanForPlugins() const;
    void populateFrom (juce::KnownPluginList::PluginTree& tree, PluginTreeGroupType t);
    void createBuiltInItems (int& num);

    JUCE_LEAK_DETECTOR (PluginTreeGroup)

};
