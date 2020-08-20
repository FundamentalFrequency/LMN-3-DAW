#include "PluginTreeGroup.h"
#include "PluginTreeItem.h"

namespace app_view_models {

    PluginTreeGroup::PluginTreeGroup(tracktion_engine::Edit &e)
            : name("Plugins"),
              edit(e)
    {

        scanForPlugins();

        auto &list = edit.engine.getPluginManager().knownPluginList;
        {
            // Add instruments group
            // Add instruments and effects group
            auto instrumentsFolder = new PluginTreeGroup(edit, "Instruments");
            auto effectsFolder = new PluginTreeGroup(edit, "Effects");
            // Populate the built in plugins
            // num is used to provide a unique identifier for the built in plugins
            int num = 1;
            // auto builtinFolder = new PluginTreeGroup(edit, "Builtin Plugins");
            addSubItem(instrumentsFolder);
            addSubItem(effectsFolder);
            instrumentsFolder->populateBuiltInInstruments(num);
            effectsFolder->populateBuiltInEffects(num);

            instrumentsFolder->populateExternalInstruments(list);
            effectsFolder->populateExternalEffects(list);

        }

    }

    PluginTreeGroup::PluginTreeGroup(tracktion_engine::Edit &e, const juce::String &s)
            : name(s),
              edit(e)
    {
        jassert(name.isNotEmpty());
    }

    juce::String PluginTreeGroup::getUniqueName() const
    {

        return name;

    }

    void PluginTreeGroup::populateExternalInstruments(juce::KnownPluginList& list)
    {

        for (const auto &description : list.getTypes()) {
                if (description.isInstrument)
                    addSubItem(new PluginTreeItem(description));

        }

    }

    void PluginTreeGroup::populateExternalEffects(juce::KnownPluginList& list)
    {

        for (const auto &description : list.getTypes()) {
            if (!description.isInstrument)
                addSubItem(new PluginTreeItem(description));

        }

    }

    template<class FilterClass>
    void addInternalPlugin(PluginTreeBase &item, int &num, bool synth = false)
    {

        item.addSubItem(new PluginTreeItem(juce::String(num++) + "_trkbuiltin",
                                           FilterClass::getPluginName(),
                                           FilterClass::xmlTypeName, synth, false));
    }


    void PluginTreeGroup::populateBuiltInInstruments(int &num)
    {

        addInternalPlugin<tracktion_engine::FourOscPlugin>(*this, num, true);
        addInternalPlugin<tracktion_engine::SamplerPlugin>(*this, num, true);


    }

    void PluginTreeGroup::populateBuiltInEffects(int &num)
    {

//        addInternalPlugin<tracktion_engine::VolumeAndPanPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::LevelMeterPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::EqualiserPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::ReverbPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::DelayPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::ChorusPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::PhaserPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::CompressorPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::PitchShiftPlugin>(*this, num);
        addInternalPlugin<tracktion_engine::LowPassPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::MidiModifierPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::MidiPatchBayPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::PatchBayPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::AuxSendPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::AuxReturnPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::TextPlugin>(*this, num);
//        addInternalPlugin<tracktion_engine::FreezePointPlugin>(*this, num);

    }

    void PluginTreeGroup::scanForPlugins() const
    {

        DBG("scan for plugins called");
        // Scan for plugins
        juce::File homeDirectory = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory);
        juce::File vst3Directory = homeDirectory.getChildFile(".vst3");
        if (!vst3Directory.exists()) {
            vst3Directory.createDirectory();

        }

        edit.engine.getPluginManager().knownPluginList.clear();

        for (auto format : edit.engine.getPluginManager().pluginFormatManager.getFormats()) {

            DBG("looking for VST3 files...");
            if (format->getName() == "VST3") {

                juce::PluginDirectoryScanner scanner(edit.engine.getPluginManager().knownPluginList,
                                                     reinterpret_cast<juce::AudioPluginFormat &>(*format),
                                                     juce::FileSearchPath(vst3Directory.getFullPathName()),
                                                     true,
                                                     edit.engine.getTemporaryFileManager().getTempFile(
                                                             "PluginScanDeadMansPedal"));

                juce::String pluginBeingScanned;
                DBG("scanning " + pluginBeingScanned);
                while (scanner.scanNextFile(false, pluginBeingScanned)) {
                    scanner.scanNextFile(false, pluginBeingScanned);
                }

            }

        }
    }

}