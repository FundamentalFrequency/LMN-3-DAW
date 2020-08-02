#include "PluginTreeBase.h"

void PluginTreeBase::addSubItem(PluginTreeBase* item)
{

    subItems.add(item);

}
int PluginTreeBase::getNumberOfSubItems()
{

    return subItems.size();

}

PluginTreeBase* PluginTreeBase::getSubItem(int index)
{

    return subItems[index];

}