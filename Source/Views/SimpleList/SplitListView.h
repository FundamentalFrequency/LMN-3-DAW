#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "SimpleListView.h"

class SplitListView
        : public juce::Component
{
public:

    SplitListView(const juce::StringArray& leftListItems, const juce::StringArray& rightListItems);

    void paint(juce::Graphics&) override;
    void resized() override;

    SimpleListView& getLeftListView();
    SimpleListView& getRightListView();

    void setLeftListItems(const juce::StringArray& listItems);
    void setRightListItems(const juce::StringArray& listItems);

private:

    SimpleListView leftListView;
    SimpleListView rightListView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SplitListView)
};

