#pragma once
#include "ListTitle.h"
#include "SplitListView.h"
#include <juce_gui_basics/juce_gui_basics.h>

class TitledSplitListView : public juce::Component {

  public:
    TitledSplitListView(const juce::StringArray &leftListItems,
                        const juce::StringArray &rightListItems,
                        const juce::String &titleString,
                        ListTitle::IconType type,
                        const juce::String &iconString);
    void paint(juce::Graphics &g) override;
    void resized() override;

    SplitListView &getSplitListView();

  private:
    SplitListView splitListView;
    ListTitle listTitle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TitledSplitListView)
};
