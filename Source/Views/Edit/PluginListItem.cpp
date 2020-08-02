#include "PluginListItem.h"

PluginListItem::PluginListItem(const juce::PluginDescription& d)
        : description(d),
          xmlType(tracktion_engine::ExternalPlugin::xmlTypeName),
          isPlugin(true)
{
    jassert (xmlType.isNotEmpty());
}


PluginListItem::PluginListItem(const juce::String& uniqueId, const juce::String& name, const juce::String& xmlType_, bool isSynth, bool isPlugin_)
        : xmlType (xmlType_), isPlugin (isPlugin_)
{
    jassert (xmlType.isNotEmpty());
    description.name = name;
    description.fileOrIdentifier = uniqueId;
    description.pluginFormatName = (uniqueId.endsWith ("_trkbuiltin") || xmlType == tracktion_engine::RackInstance::xmlTypeName)
                            ? getInternalPluginFormatName() : juce::String();
    description.category = xmlType;
    description.isInstrument = isSynth;
}

tracktion_engine::Plugin::Ptr PluginListItem::create(tracktion_engine::Edit& ed)
{
    return ed.getPluginCache().createNewPlugin(xmlType, description);
}