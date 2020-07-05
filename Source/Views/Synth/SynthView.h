#include <juce_gui_extra/juce_gui_extra.h>
class SynthView : public juce::TabbedComponent,
                  public juce::ApplicationCommandTarget
{
public:
    SynthView();

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;
    
private:
    juce::String engineTabName = "ENGINE";
    juce::String adsrTabName = "ADSR";
    juce::String effectTabName = "EFFECT";
    juce::String lfoTabName = "LFO";

    juce::ApplicationCommandManager commandManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthView)
};

