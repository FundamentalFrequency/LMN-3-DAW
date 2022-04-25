#pragma once
#include "PluginTreeBase.h"
#include <tracktion_engine/tracktion_engine.h>

namespace app_view_models {
class PluginTreeGroup : public PluginTreeBase {

  public:
    PluginTreeGroup(tracktion_engine::Edit &e);

    PluginTreeGroup(tracktion_engine::Edit &e, const juce::String &s);

    juce::String getUniqueName() const override;

    juce::String name;

  private:
    tracktion_engine::Edit &edit;

    void scanForPlugins() const;

    void populateExternalInstruments(juce::KnownPluginList &list);
    void populateExternalEffects(juce::KnownPluginList &list);

    void populateBuiltInInstruments(int &num);
    void populateBuiltInEffects(int &num);

    JUCE_LEAK_DETECTOR(PluginTreeGroup)
};
} // namespace app_view_models