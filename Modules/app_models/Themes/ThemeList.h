#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_data_structures/juce_data_structures.h>
#include "Theme.h"
class ThemeList : public tracktion_engine::ValueTreeObjectList<Theme>
{

public:
    ThemeList(const juce::ValueTree& v);
    ~ThemeList();

    bool isSuitableType(const juce::ValueTree& v) const override;
    Theme* createNewObject(const juce::ValueTree& v) override;
    void deleteObject(Theme* t) override;
    void newObjectAdded(Theme* t) override;
    void objectRemoved(Theme* t) override;
    void objectOrderChanged() override;


};




