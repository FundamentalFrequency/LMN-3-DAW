#pragma once

namespace app_view_models {

    class FlaggedAsyncUpdater : public juce::AsyncUpdater {

    public:

        void markAndUpdate (bool& flag);

        bool compareAndReset (bool& flag) noexcept;

    };

}
