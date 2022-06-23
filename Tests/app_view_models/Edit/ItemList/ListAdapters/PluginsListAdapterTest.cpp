#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class PluginsListAdapterTest : public ::testing::Test {
  protected:
    PluginsListAdapterTest()
        : edit(tracktion::Edit::createSingleTrackEdit(engine)), group(*edit),
          adapter(tracktion::getAudioTracks(*edit)[0]) {}

    void SetUp() override {
        auto track = tracktion::getAudioTracks(*edit)[0];

        // Add 2 effects from the plugin effects group to the track
        // we will add the equaliser and the Reverb
        // effects is group at index 1
        if (auto selectedPluginItem =
                dynamic_cast<app_view_models::PluginTreeItem *>(
                    group.getSubItem(1)->getSubItem(0)))
            track->pluginList.insertPlugin(
                selectedPluginItem->create(track->edit), -1, nullptr);

        if (auto selectedPluginItem =
                dynamic_cast<app_view_models::PluginTreeItem *>(
                    group.getSubItem(1)->getSubItem(1)))
            track->pluginList.insertPlugin(
                selectedPluginItem->create(track->edit), -1, nullptr);
    }

    tracktion::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion::Edit> edit;
    app_view_models::PluginsListAdapter adapter;
    app_view_models::PluginTreeGroup group;
};

TEST_F(PluginsListAdapterTest, size) { EXPECT_EQ(adapter.size(), 2); }

TEST_F(PluginsListAdapterTest, getItemNames) {
    EXPECT_EQ(adapter.getItemNames().size(), 2);
    EXPECT_EQ(adapter.getItemNames()[0], juce::String("4-Band Equaliser"));
    EXPECT_EQ(adapter.getItemNames()[1], juce::String("Reverb"));
}

TEST_F(PluginsListAdapterTest, getItemAtIndex) {
    EXPECT_EQ(adapter.getItemAtIndex(0)->getName(),
              juce::String("4-Band Equaliser"));
    EXPECT_EQ(adapter.getItemAtIndex(1)->getName(), juce::String("Reverb"));
    EXPECT_EQ(adapter.getItemAtIndex(2), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(50), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-1), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-50), nullptr);
}

} // namespace AppViewModelsTests