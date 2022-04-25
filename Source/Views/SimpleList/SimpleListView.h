#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "SimpleListModel.h"
class SimpleListView : public juce::Component {

public:

    explicit SimpleListView(const juce::StringArray& listItems);

    void paint(juce::Graphics& g) override;
    void resized() override;

    juce::ListBox& getListBox();
    void setListItems(const juce::StringArray& listItems);

private:
    juce::ListBox listBox;
    std::unique_ptr<SimpleListModel> listModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleListView)
};



