#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests
{

    class PluginsListAdapterTest : public ::testing::Test {
    protected:

        PluginsListAdapterTest()
                : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  adapter(tracktion_engine::getAudioTracks(*edit)[0]) {}

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::PluginsListAdapter adapter;

    };

    TEST_F(PluginsListAdapterTest, size)
    {

        EXPECT_EQ(adapter.size(), 2);

    }

    TEST_F(PluginsListAdapterTest, getItemNames)
    {

        EXPECT_EQ(adapter.getItemNames().size(), 2);
        EXPECT_EQ(adapter.getItemNames()[0], juce::String("Volume & Pan Plugin"));
        EXPECT_EQ(adapter.getItemNames()[1], juce::String("Level Meter"));

    }

    TEST_F(PluginsListAdapterTest, getItemAtIndex)
    {

        EXPECT_EQ(adapter.getItemAtIndex(0)->getName(), juce::String("Volume & Pan Plugin"));
        EXPECT_EQ(adapter.getItemAtIndex(1)->getName(),  juce::String("Level Meter"));
        EXPECT_EQ(adapter.getItemAtIndex(2), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(50), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(-1), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(-50), nullptr);

    }


}