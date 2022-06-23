#include "PluginTreeItem.h"

namespace app_view_models {

PluginTreeItem::PluginTreeItem(const juce::PluginDescription &desc)
    : description(desc), xmlType(tracktion::ExternalPlugin::xmlTypeName),
      isPlugin(true) {
    jassert(xmlType.isNotEmpty());
}

PluginTreeItem::PluginTreeItem(const juce::String &uniqueId,
                               const juce::String &name,
                               const juce::String &xmlType_, bool isSynth,
                               bool isPlugin_)
    : xmlType(xmlType_), isPlugin(isPlugin_) {
    jassert(xmlType.isNotEmpty());
    description.name = name;
    description.fileOrIdentifier = uniqueId;
    description.pluginFormatName =
        (uniqueId.endsWith("_trkbuiltin") ||
         xmlType == tracktion::RackInstance::xmlTypeName)
            ? getInternalPluginFormatName()
            : juce::String();
    description.category = xmlType;
    description.isInstrument = isSynth;
}

tracktion::Plugin::Ptr
PluginTreeItem::create(tracktion::Edit &edit) {
    return edit.getPluginCache().createNewPlugin(xmlType, description);
}

juce::String PluginTreeItem::getUniqueName() const {
    if (description.fileOrIdentifier.startsWith(
            tracktion::RackType::getRackPresetPrefix()))
        return description.fileOrIdentifier;

    return description.createIdentifierString();
}
} // namespace app_view_models