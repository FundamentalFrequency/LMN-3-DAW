#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class TracksListAdapterTest : public ::testing::Test {
  protected:
    TracksListAdapterTest()
        : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
          adapter(*edit) {}

    void SetUp() override { edit->ensureNumberOfAudioTracks(8); }

    tracktion_engine::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion_engine::Edit> edit;
    app_view_models::TracksListAdapter adapter;
};

TEST_F(TracksListAdapterTest, size) { EXPECT_EQ(adapter.size(), 8); }

TEST_F(TracksListAdapterTest, getItemNames) {
    EXPECT_EQ(adapter.getItemNames().size(), 8);
    EXPECT_EQ(adapter.getItemNames()[0], juce::String("Track 1"));
    EXPECT_EQ(adapter.getItemNames()[7], juce::String("Track 8"));
}

TEST_F(TracksListAdapterTest, getItemAtIndex) {
    EXPECT_EQ(adapter.getItemAtIndex(0)->getName(), juce::String("Track 1"));
    EXPECT_EQ(adapter.getItemAtIndex(3)->getName(), juce::String("Track 4"));
    EXPECT_EQ(adapter.getItemAtIndex(7)->getName(), juce::String("Track 8"));
    EXPECT_EQ(adapter.getItemAtIndex(8), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(50), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-1), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-50), nullptr);
}

} // namespace AppViewModelsTests