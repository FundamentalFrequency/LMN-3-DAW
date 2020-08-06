#pragma once
#include <tracktion_engine/tracktion_engine.h>
bool isDPIAware (tracktion_engine::Plugin&)
{
    // You should keep a DB of if plugins are DPI aware or not and recall that value
    // here. You should let the user toggle the value if the plugin appears tiny
    return true;
}

//==============================================================================
class PluginEditor : public juce::Component
{
public:
    virtual bool allowWindowResizing() = 0;
    virtual juce::ComponentBoundsConstrainer* getBoundsConstrainer() = 0;
};

//==============================================================================
struct AudioProcessorEditorContentComp : public PluginEditor
{
    AudioProcessorEditorContentComp (tracktion_engine::ExternalPlugin& plug) : plugin (plug)
    {
        JUCE_AUTORELEASEPOOL
        {
            if (auto pi = plugin.getAudioPluginInstance())
            {
                editor.reset (pi->createEditorIfNeeded());

                if (editor == nullptr)
                    editor = std::make_unique<juce::GenericAudioProcessorEditor> (*pi);

                addAndMakeVisible (*editor);
            }
        }

        resizeToFitEditor (true);
    }

    bool allowWindowResizing() override { return false; }

    juce::ComponentBoundsConstrainer* getBoundsConstrainer() override
    {
        if (editor == nullptr || allowWindowResizing())
            return {};

        return editor->getConstrainer();
    }

    void resized() override
    {
        if (editor != nullptr)
            editor->setBounds (getLocalBounds());
    }

    void childBoundsChanged (Component* c) override
    {
        if (c == editor.get())
        {
            plugin.edit.pluginChanged (plugin);
            resizeToFitEditor();
        }
    }

    void resizeToFitEditor (bool force = false)
    {
        if (force || ! allowWindowResizing())
            setSize (juce::jmax (8, editor != nullptr ? editor->getWidth() : 0), juce::jmax (8, editor != nullptr ? editor->getHeight() : 0));
    }

    tracktion_engine::ExternalPlugin& plugin;
    std::unique_ptr<juce::AudioProcessorEditor> editor;

    AudioProcessorEditorContentComp() = delete;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorEditorContentComp)
};

//=============================================================================
class PluginWindow : public juce::DocumentWindow
{
public:
    PluginWindow (tracktion_engine::Plugin&);
    ~PluginWindow() override;

    static std::unique_ptr<Component> create (tracktion_engine::Plugin&);

    void show();

    void setEditor (std::unique_ptr<PluginEditor>);
    PluginEditor* getEditor() const         { return editor.get(); }

    void recreateEditor();
    void recreateEditorAsync();
    std::unique_ptr<PluginEditor> createContentComp();

private:
    void moved() override;
    void userTriedToCloseWindow() override          { plugin.windowState->closeWindowExplicitly(); }
    void closeButtonPressed() override              { userTriedToCloseWindow(); }
    float getDesktopScaleFactor() const override    { return 1.0f; }



    std::unique_ptr<PluginEditor> editor;

    tracktion_engine::Plugin& plugin;
    tracktion_engine::PluginWindowState& windowState;
};

//==============================================================================
#if JUCE_LINUX
constexpr bool shouldAddPluginWindowToDesktop = false;
#else
constexpr bool shouldAddPluginWindowToDesktop = true;
#endif

PluginWindow::PluginWindow (tracktion_engine::Plugin& plug)
        : DocumentWindow (plug.getName(), juce::Colours::black, DocumentWindow::closeButton, shouldAddPluginWindowToDesktop),
          plugin (plug), windowState (*plug.windowState)
{
    getConstrainer()->setMinimumOnscreenAmounts (0x10000, 50, 30, 50);

    auto position = plugin.windowState->lastWindowBounds.getPosition();
    setBounds (getLocalBounds() + position);

    setResizeLimits (100, 50, 4000, 4000);
    setBoundsConstrained (getLocalBounds() + position);

    recreateEditor();

#if JUCE_LINUX
    setAlwaysOnTop (true);
     addToDesktop();
#endif
}

PluginWindow::~PluginWindow()
{
    plugin.edit.flushPluginStateIfNeeded (plugin);
    setEditor (nullptr);
}

void PluginWindow::show()
{
    setVisible (true);
    toFront (false);
    setBoundsConstrained (getBounds());
}

void PluginWindow::setEditor (std::unique_ptr<PluginEditor> newEditor)
{
    JUCE_AUTORELEASEPOOL
    {
        setConstrainer (nullptr);
        editor.reset();

        if (newEditor != nullptr)
        {
            editor = std::move (newEditor);
            setContentNonOwned (editor.get(), true);
        }

        setResizable (editor == nullptr || editor->allowWindowResizing(), false);

        if (editor != nullptr && editor->allowWindowResizing())
            setConstrainer (editor->getBoundsConstrainer());
    }
}

std::unique_ptr<juce::Component> PluginWindow::create (tracktion_engine::Plugin& plugin)
{
    if (auto externalPlugin = dynamic_cast<tracktion_engine::ExternalPlugin*> (&plugin))
        if (externalPlugin->getAudioPluginInstance() == nullptr)
            return nullptr;

    std::unique_ptr<PluginWindow> w;

    {
        struct Blocker : public Component { void inputAttemptWhenModal() override {} };

        Blocker blocker;
        blocker.enterModalState (false);

#if JUCE_WINDOWS && JUCE_WIN_PER_MONITOR_DPI_AWARE
        if (! isDPIAware (plugin))
        {
            ScopedDPIAwarenessDisabler disableDPIAwareness;
            w = std::make_unique<PluginWindow> (plugin);
        }
        else
#endif
        {
            w = std::make_unique<PluginWindow> (plugin);
        }
    }

    if (w == nullptr || w->getEditor() == nullptr)
        return {};

    w->show();

    return w;
}

std::unique_ptr<PluginEditor> PluginWindow::createContentComp()
{
    if (auto ex = dynamic_cast<tracktion_engine::ExternalPlugin*> (&plugin))
        return std::make_unique<AudioProcessorEditorContentComp> (*ex);

    return nullptr;
}

void PluginWindow::recreateEditor()
{
    setEditor (nullptr);
    setEditor (createContentComp());
}

void PluginWindow::recreateEditorAsync()
{
    setEditor (nullptr);

    juce::Timer::callAfterDelay (50, [this, sp = SafePointer<Component> (this)]
    {
        if (sp != nullptr)
            recreateEditor();
    });
}

void PluginWindow::moved()
{
    plugin.windowState->lastWindowBounds = getBounds();
    plugin.edit.pluginChanged (plugin);
}

//==============================================================================
class ExtendedUIBehaviour : public tracktion_engine::UIBehaviour
{
public:
    ExtendedUIBehaviour() = default;

    std::unique_ptr<juce::Component> createPluginWindow (tracktion_engine::PluginWindowState& pws) override
    {
        if (auto ws = dynamic_cast<tracktion_engine::Plugin::WindowState*> (&pws))
        {
            //return PluginWindow::create (ws->plugin);
            auto component = PluginWindow::create(ws->plugin);
            if (auto window = dynamic_cast<PluginWindow*>(component.get()))
            {
                return window->createContentComp();
            }
        }


        return {};
    }

    void recreatePluginWindowContentAsync (tracktion_engine::Plugin& p) override
    {
        if (auto* w = dynamic_cast<PluginWindow*> (p.windowState->pluginWindow.get()))
            return w->recreateEditorAsync();

        UIBehaviour::recreatePluginWindowContentAsync (p);
    }
};