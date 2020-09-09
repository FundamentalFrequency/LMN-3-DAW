#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "SimpleListView.h"
#include "ListTitle.h"

class TitledListView
    : public juce::Component
{

public:

    TitledListView(const juce::StringArray& listItems, const juce::String& titleString, ListTitle::IconType type, const juce::String& iconString);

    void paint(juce::Graphics& g) override;
    void resized() override;

    SimpleListView& getListView();

    void setListItems(const juce::StringArray& listItems);

private:

    SimpleListView listView;
    ListTitle listTitle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TitledListView)

};


