#include "MidiCommandInfo.h"
MidiCommandInfo::MidiCommandInfo(const MidiCommandID cid) noexcept
    : commandID(cid)
{

}

void MidiCommandInfo::setInfo(const juce::String& shortName_,
                               const juce::String& description_,
                               const juce::String& categoryName_,
                               const int flags_) noexcept
{
    shortName = shortName_;
    description = description_;
    categoryName = categoryName_;
    flags = flags_;
}

void MidiCommandInfo::setActive(const bool b) noexcept
{
    if (b)
        flags &= ~isDisabled;
    else
        flags |= isDisabled;
}

void MidiCommandInfo::setTicked(const bool b) noexcept
{
    if (b)
        flags |= isTicked;
    else
        flags &= ~isTicked;
}

void MidiCommandInfo::addDefaultMidiControlChange(const int controller) noexcept
{
    defaultMidiControlChanges.add(controller);
}


