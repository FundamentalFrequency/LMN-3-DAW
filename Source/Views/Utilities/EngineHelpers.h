#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_basics/juce_gui_basics.h>
namespace EngineHelpers
{
    tracktion_engine::Project::Ptr createTempProject(tracktion_engine::Engine& engine)
    {
        auto file = engine.getTemporaryFileManager().getTempDirectory().getChildFile ("temp_project").withFileExtension(tracktion_engine::projectFileSuffix);
        tracktion_engine::ProjectManager::TempProject tempProject (engine.getProjectManager(), file, true);
        return tempProject.project;
    }

    void showAudioDeviceSettings(tracktion_engine::Engine& engine)
    {
        juce::DialogWindow::LaunchOptions o;
        o.dialogTitle = "Audio Settings";
        o.dialogBackgroundColour = juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
        o.content.setOwned(new juce::AudioDeviceSelectorComponent(engine.getDeviceManager().deviceManager,
                                                              0, 512, 1, 512, false, false, true, true));
        o.content->setSize(400, 600);
        o.launchAsync();
    }

    void browseForAudioFile(tracktion_engine::Engine& engine, std::function<void(const juce::File&)> fileChosenCallback)
    {
        auto fc = std::make_shared<juce::FileChooser> ("Please select an audio file to load...",
                                                 engine.getPropertyStorage().getDefaultLoadSaveDirectory ("pitchAndTimeExample"),
                                                 engine.getAudioFileFormatManager().readFormatManager.getWildcardForAllFormats());

        fc->launchAsync(juce::FileBrowserComponent::openMode + juce::FileBrowserComponent::canSelectFiles,
                         [fc, &engine, callback = std::move(fileChosenCallback)] (const juce::FileChooser&)
                         {
                             const auto f = fc->getResult();

                             if (f.existsAsFile())
                                 engine.getPropertyStorage().setDefaultLoadSaveDirectory("pitchAndTimeExample", f.getParentDirectory());

                             callback (f);
                         });
    }

    void removeAllClips(tracktion_engine::AudioTrack& track)
    {
        auto clips = track.getClips();

        for (int i = clips.size(); --i >= 0;)
            clips.getUnchecked (i)->removeFromParentTrack();
    }

    tracktion_engine::AudioTrack* getOrInsertAudioTrackAt(tracktion_engine::Edit& edit, int index)
    {
        edit.ensureNumberOfAudioTracks(index + 1);
        return tracktion_engine::getAudioTracks(edit)[index];
    }

    tracktion_engine::WaveAudioClip::Ptr loadAudioFileAsClip(tracktion_engine::Edit& edit, const juce::File& file)
    {
        // Find the first track and delete all clips from it
        if (auto track = getOrInsertAudioTrackAt (edit, 0))
        {
            removeAllClips (*track);

            // Add a new clip to this track
            tracktion_engine::AudioFile audioFile (edit.engine, file);

            if (audioFile.isValid())
                if (auto newClip = track->insertWaveClip(file.getFileNameWithoutExtension(), file,
                                                          { { 0.0, audioFile.getLength() }, 0.0 }, false))
                    return newClip;
        }

        return {};
    }

    template<typename ClipType>
    typename ClipType::Ptr loopAroundClip(ClipType& clip)
    {
        auto& transport = clip.edit.getTransport();
        transport.setLoopRange (clip.getEditTimeRange());
        transport.looping = true;
        transport.position = 0.0;
        transport.play (false);

        return clip;
    }

    void togglePlay(tracktion_engine::Edit& edit)
    {
        auto& transport = edit.getTransport();

        if (transport.isPlaying())
            transport.stop (false, false);
        else
            transport.play (false);
    }

    void toggleRecord(tracktion_engine::Edit& edit)
    {
        auto& transport = edit.getTransport();

        if (transport.isRecording())
            transport.stop(true, false);
        else
            transport.record(false);
    }

    void armTrack(tracktion_engine::AudioTrack& t, bool arm, int position = 0)
    {
        auto& edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack(t, position))
                instance->setRecordingEnabled(t, arm);
    }

    bool isTrackArmed(tracktion_engine::AudioTrack& t, int position = 0)
    {
        auto& edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack(t, position))
                return instance->isRecordingEnabled (t);

        return false;
    }

    bool isInputMonitoringEnabled(tracktion_engine::AudioTrack& t, int position = 0)
    {
        auto& edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack (t, position))
                return instance->getInputDevice().isEndToEndEnabled();

        return false;
    }

    void enableInputMonitoring(tracktion_engine::AudioTrack& t, bool im, int position = 0)
    {
        if (isInputMonitoringEnabled (t, position) != im)
        {
            auto& edit = t.edit;
            for (auto instance : edit.getAllInputDevices())
                if (instance->isOnTargetTrack (t, position))
                    instance->getInputDevice().flipEndToEnd();
        }
    }

    bool trackHasInput(tracktion_engine::AudioTrack& t, int position = 0)
    {
        auto& edit = t.edit;
        for (auto instance : edit.getAllInputDevices())
            if (instance->isOnTargetTrack (t, position))
                return true;

        return false;
    }

    inline std::unique_ptr<juce::KnownPluginList::PluginTree> createPluginTree(tracktion_engine::Engine& engine)
    {
        auto& list = engine.getPluginManager().knownPluginList;

        if (auto tree = list.createTree(list.getTypes(), juce::KnownPluginList::sortByManufacturer))
            return tree;

        return {};
    }

}