#include "SplitListBoxModel.h"
#include "ListRow.h"
#include "PluginTreeItem.h"
SplitListBoxModel::SplitListBoxModel(PluginTreeGroup& t)
        : tree(t),
          selectedBackgroundColour(juce::Colours::black)
{


}
int SplitListBoxModel::getNumRows()
{
    return tree.getNumberOfSubItems();
}
void SplitListBoxModel::paintListBoxItem (int rowNumber,
                                          juce::Graphics& g,
                                          int width, int height,
                                          bool rowIsSelected)
{

}

juce::Component* SplitListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    auto* row = dynamic_cast<ListRow*>(existingComponentToUpdate);

    if(rowNumber < tree.getNumberOfSubItems())
    {
        if(!row)
        {

            if (auto subTree = dynamic_cast<PluginTreeGroup*>(tree.getSubItem(rowNumber)))
                row = new ListRow(subTree->name);

            if (auto subTree = dynamic_cast<PluginTreeItem*>(tree.getSubItem(rowNumber)))
                row = new ListRow(subTree->description.name);
        }

        if (row != nullptr)
        {

            /* Update all properties of your custom component with the data for the current row  */
            if (auto subTree = dynamic_cast<PluginTreeGroup*>(tree.getSubItem(rowNumber)))
                row->setTitle(subTree->name);


            if (auto subTree = dynamic_cast<PluginTreeItem*>(tree.getSubItem(rowNumber)))
                row->setTitle(subTree->description.name);

            row->setSelectedBackgroundColour(selectedBackgroundColour);
            row->setSelected(isRowSelected);

        }

    }
    else
    {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;
    }

    return row;
}

PluginTreeGroup& SplitListBoxModel::getPluginTreeGroup()
{

    return tree;

}

void SplitListBoxModel::setSelectedBackgroundColour(juce::Colour selectedBackgroundColour_)
{

    selectedBackgroundColour = selectedBackgroundColour_;

}

