#include "PluginTreeBase.h"

namespace app_view_models {

void PluginTreeBase::addSubItem(PluginTreeBase *item) { subItems.add(item); }

int PluginTreeBase::getNumberOfSubItems() { return subItems.size(); }

PluginTreeBase *PluginTreeBase::getSubItem(int index) {
    return subItems[index];
}

} // namespace app_view_models