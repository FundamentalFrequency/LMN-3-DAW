#include "SynthEngineListView.h"
#include <juce_audio_processors/juce_audio_processors.h>
SynthEngineListView::SynthEngineListView(tracktion_engine::PluginManager& pm, tracktion_engine::TemporaryFileManager& tm, juce::ApplicationCommandManager& cm)
    : pluginManager(pm),
      temporaryFileManager(tm),
      commandManager(cm)
{

    juce::File homeDirectory  = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory);
    juce::File vst3Directory = homeDirectory.getChildFile(".vst3");
    if (!vst3Directory.exists())
    {
        vst3Directory.createDirectory();

    }
    juce::File appPluginsDirectory = vst3Directory.getChildFile("APP");
    if (!appPluginsDirectory.exists())
    {
        appPluginsDirectory.createDirectory();
    }

    pluginManager.knownPluginList.clear();

    for (auto format : pluginManager.pluginFormatManager.getFormats())
    {
        if (format->getName() == "VST3")
        {

            juce::PluginDirectoryScanner scanner(pluginManager.knownPluginList,
                                                 reinterpret_cast<juce::AudioPluginFormat &>(*format),
                                                 juce::FileSearchPath(appPluginsDirectory.getFullPathName()),
                                                 true,
                                                 temporaryFileManager.getTempFile ("PluginScanDeadMansPedal"));

            juce::String pluginBeingScanned;
            while (scanner.scanNextFile(false, pluginBeingScanned))
            {
                scanner.scanNextFile(false, pluginBeingScanned);
            }

        }

    }

    listModel = std::make_unique<SynthEngineListBoxModel>(pluginManager.knownPluginList.getTypes());
    listBox.setModel(listModel.get());
    listBox.selectRow(0);
    addAndMakeVisible(listBox);

}

void SynthEngineListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void SynthEngineListView::resized()
{

    listBox.setBounds(getLocalBounds());
    listBox.setRowHeight (getParentHeight() / 10);

}
