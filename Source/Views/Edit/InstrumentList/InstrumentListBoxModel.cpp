#include "InstrumentListBoxModel.h"
#include "InstrumentListRow.h"
InstrumentListBoxModel::InstrumentListBoxModel(juce::Array<PluginListItem> listItems)
        : items(listItems)
{


}
int InstrumentListBoxModel::getNumRows()
{
    return items.size();
}
void InstrumentListBoxModel::paintListBoxItem (int rowNumber,
                                                juce::Graphics& g,
                                                int width, int height,
                                                bool rowIsSelected)
{

}

juce::Component* InstrumentListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    auto* row = dynamic_cast<InstrumentListRow*>(existingComponentToUpdate);

    if(rowNumber < items.size())
    {
        if(!row)
            row = new InstrumentListRow(items.getUnchecked(rowNumber).description.name);

        /* Update all properties of your custom component with the data for the current row  */
        row->setTitle(items.getUnchecked(rowNumber).description.name);
        row->setSelected(isRowSelected);

    }
    else
    {
        // Nothing to display, free the custom component
        delete existingComponentToUpdate;
        row = nullptr;
    }

    return row;
}