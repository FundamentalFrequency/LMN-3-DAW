#include "InstrumentListBoxModel.h"
#include "InstrumentListRow.h"
InstrumentListBoxModel::InstrumentListBoxModel(juce::Array<juce::PluginDescription> descriptions)
        : pluginDescriptions(descriptions)
{


}
int InstrumentListBoxModel::getNumRows()
{
    return pluginDescriptions.size();
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

    if(rowNumber < pluginDescriptions.size())
    {
        if(!row)
            row = new InstrumentListRow(pluginDescriptions.getUnchecked(rowNumber).name);

        /* Update all properties of your custom component with the data for the current row  */
        row->setTitle(pluginDescriptions.getUnchecked(rowNumber).name);
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