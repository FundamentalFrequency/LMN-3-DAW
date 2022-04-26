#include "FlaggedAsyncUpdater.h"

namespace app_view_models {
void FlaggedAsyncUpdater::markAndUpdate(bool &flag) {
    flag = true;
    triggerAsyncUpdate();
}

bool FlaggedAsyncUpdater::compareAndReset(bool &flag) noexcept {
    if (!flag)
        return false;

    flag = false;
    return true;
}
} // namespace app_view_models