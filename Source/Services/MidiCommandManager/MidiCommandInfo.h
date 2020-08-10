#pragma once
#include <juce_core/juce_core.h>
using MidiCommandID = int;

struct MidiCommandInfo {

    explicit MidiCommandInfo(const MidiCommandID cid) noexcept;

    void setInfo (const juce::String& shortName_,
                  const juce::String& description_,
                  const juce::String& categoryName_,
                  const int flags_) noexcept;

    void setActive(const bool isActive) noexcept;

    void setTicked(const bool isTicked) noexcept;

    void addDefaultMidiControlChange(const int controller) noexcept;

    MidiCommandID commandID;
    juce::String shortName;
    juce::String description;
    juce::String categoryName;

    juce::Array<int> defaultMidiControlChanges;

    enum CommandFlags
    {
        isDisabled                  = 1 << 0,
        isTicked                    = 1 << 1,
        wantsKeyUpDownCallbacks     = 1 << 2,
        hiddenFromKeyEditor         = 1 << 3,
        readOnlyInKeyEditor         = 1 << 4,
        dontTriggerVisualFeedback   = 1 << 5
    };

    int flags;

};



