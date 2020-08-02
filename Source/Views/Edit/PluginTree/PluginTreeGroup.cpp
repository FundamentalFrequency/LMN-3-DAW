#include "PluginTreeGroup.h"
#include "PluginTreeItem.h"

PluginTreeGroup::PluginTreeGroup(tracktion_engine::Edit& edit, juce::KnownPluginList::PluginTree& tree, tracktion_engine::Plugin::Type types)
    : name("Plugins")
{

    {
        // Populate the built in plugins
        // num is used to provide a unique identifier for the built in plugins
        int num = 1;
        auto builtinFolder = new PluginTreeGroup(TRANS("APP"));
        addSubItem(builtinFolder);
        builtinFolder->createBuiltInItems(num, types);

    }

    // now populate the VST3 plugns
    populateFrom (tree);


}

PluginTreeGroup::PluginTreeGroup(const juce::String&)
{
    jassert(name.isNotEmpty());
}

juce::String PluginTreeGroup::getUniqueName() const
{

    return name;
}

void PluginTreeGroup::populateFrom(juce::KnownPluginList::PluginTree& tree)
{

    for (auto subTree : tree.subFolders)
    {
        if (subTree->plugins.size() > 0 || subTree->subFolders.size() > 0)
        {
            auto fs = new PluginTreeGroup (subTree->folder);
            addSubItem (fs);

            fs->populateFrom (*subTree);
        }
    }

    for (const auto& pd : tree.plugins)
        addSubItem (new PluginTreeItem (pd));

}

template<class FilterClass>
void addInternalPlugin (PluginTreeBase& item, int& num, bool synth = false)
{
    item.addSubItem (new PluginTreeItem(juce::String(num++) + "_trkbuiltin",
                     TRANS (FilterClass::getPluginName()),
                     FilterClass::xmlTypeName, synth, false));
}


void PluginTreeGroup::createBuiltInItems(int& num, tracktion_engine::Plugin::Type types)
{
    addInternalPlugin<tracktion_engine::VolumeAndPanPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::LevelMeterPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::EqualiserPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::ReverbPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::DelayPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::ChorusPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::PhaserPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::CompressorPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::PitchShiftPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::LowPassPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::MidiModifierPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::MidiPatchBayPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::PatchBayPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::AuxSendPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::AuxReturnPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::TextPlugin>(*this, num);
    addInternalPlugin<tracktion_engine::FreezePointPlugin>(*this, num);

    if (types == tracktion_engine::Plugin::Type::allPlugins)
    {
        addInternalPlugin<tracktion_engine::SamplerPlugin> (*this, num, true);
        addInternalPlugin<tracktion_engine::FourOscPlugin> (*this, num, true);
    }

}