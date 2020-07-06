#include "ThemeList.h"
#include "Identifiers.h"

ThemeList::ThemeList(const juce::ValueTree& v)
    : tracktion_engine::ValueTreeObjectList<Theme>(v)
{
    rebuildObjects();
}
ThemeList::~ThemeList()
{
    freeObjects();
}

bool ThemeList::isSuitableType(const juce::ValueTree& v) const
{
    return v.hasType(IDs::THEME);
}

Theme* ThemeList::createNewObject(const juce::ValueTree& v)
{

    return new Theme(v);
}

void ThemeList::deleteObject(Theme* t)
{
    delete t;
}
void ThemeList::newObjectAdded(Theme* t)
{

}

void ThemeList::objectRemoved(Theme* t)
{

}

void ThemeList::objectOrderChanged()
{

}