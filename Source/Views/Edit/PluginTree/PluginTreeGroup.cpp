#include "PluginTreeGroup.h"
#include "PluginTreeItem.h"

PluginTreeGroup::PluginTreeGroup(tracktion_engine::Edit& e, PluginTreeGroupType t)
    : name("Plugins"),
      edit(e),
      type(t)
{

    scanForPlugins();

    auto& list = edit.engine.getPluginManager().knownPluginList;
    auto tree = list.createTree(list.getTypes(), juce::KnownPluginList::sortByManufacturer);

    {
        // Populate the built in plugins
        // num is used to provide a unique identifier for the built in plugins
        int num = 1;
        auto builtinFolder = new PluginTreeGroup(edit, type, "Builtin Plugins");
        addSubItem(builtinFolder);
        builtinFolder->createBuiltInItems(num);

    }

    // now populate the VST3 plugns
    populateFrom (*tree, type);


}

PluginTreeGroup::PluginTreeGroup(tracktion_engine::Edit& e, PluginTreeGroupType t, const juce::String& s)
    : name(s),
      edit(e),
      type(t)
{
    jassert(name.isNotEmpty());
}

juce::String PluginTreeGroup::getUniqueName() const
{

    return name;

}

void PluginTreeGroup::populateFrom(juce::KnownPluginList::PluginTree& tree, PluginTreeGroupType t)
{

    for (auto subTree : tree.subFolders)
    {
        if (subTree->plugins.size() > 0 || subTree->subFolders.size() > 0)
        {
            auto fs = new PluginTreeGroup(edit, t, subTree->folder);
            addSubItem(fs);

            fs->populateFrom(*subTree, type);
        }
    }

    for (const auto& description : tree.plugins)
    {
        if (type == PluginTreeGroupType::INSTRUMENTS)
        {
            if (description.isInstrument)
                addSubItem(new PluginTreeItem(description));
        }

        if (type == PluginTreeGroupType::EFFECTS)
        {
            if (!description.isInstrument)
                addSubItem(new PluginTreeItem(description));
        }

    }


}

template<class FilterClass>
void addInternalPlugin (PluginTreeBase& item, int& num, bool synth = false)
{
    item.addSubItem (new PluginTreeItem(juce::String(num++) + "_trkbuiltin",
                     FilterClass::getPluginName(),
                     FilterClass::xmlTypeName, synth, false));
}


void PluginTreeGroup::createBuiltInItems(int& num)
{

    if (type == PluginTreeGroupType::INSTRUMENTS)
    {

        addInternalPlugin<tracktion_engine::SamplerPlugin> (*this, num, true);
        addInternalPlugin<tracktion_engine::FourOscPlugin> (*this, num, true);

    }

    if (type == PluginTreeGroupType::EFFECTS)
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
    }

}

void PluginTreeGroup::scanForPlugins() const
{

    // Scan for plugins
    juce::File homeDirectory  = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory);
    juce::File vst3Directory = homeDirectory.getChildFile(".vst3");
    if (!vst3Directory.exists())
    {
        vst3Directory.createDirectory();

    }

    edit.engine.getPluginManager().knownPluginList.clear();

    for (auto format : edit.engine.getPluginManager().pluginFormatManager.getFormats())
    {
        if (format->getName() == "VST3")
        {

            juce::PluginDirectoryScanner scanner( edit.engine.getPluginManager().knownPluginList,
                                                  reinterpret_cast<juce::AudioPluginFormat &>(*format),
                                                  juce::FileSearchPath(vst3Directory.getFullPathName()),
                                                  true,
                                                  edit.engine.getTemporaryFileManager().getTempFile ("PluginScanDeadMansPedal"));

            juce::String pluginBeingScanned;
            while (scanner.scanNextFile(false, pluginBeingScanned))
            {
                scanner.scanNextFile(false, pluginBeingScanned);
            }

        }

    }
}