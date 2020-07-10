#include "PresetSlotList.h"
#include "Identifiers.h"

PresetSlotList::PresetSlotList(const juce::ValueTree& v)
        : tracktion_engine::ValueTreeObjectList<PresetSlot>(v)
{
    rebuildObjects();
}
PresetSlotList::~PresetSlotList()
{
    freeObjects();
}

bool PresetSlotList::isSuitableType(const juce::ValueTree& v) const
{
    return v.hasType(IDs::PRESET_SLOT);
}

PresetSlot* PresetSlotList::createNewObject(const juce::ValueTree& v)
{

    return new PresetSlot(v);
}

void PresetSlotList::deleteObject(PresetSlot* ps)
{
    delete ps;
}
void PresetSlotList::newObjectAdded(PresetSlot* ps)
{

}

void PresetSlotList::objectRemoved(PresetSlot* ps)
{

}

void PresetSlotList::objectOrderChanged()
{

}