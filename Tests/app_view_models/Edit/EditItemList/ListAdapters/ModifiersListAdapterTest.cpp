#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests
{

    class ModifiersListAdapterTest : public ::testing::Test {
    protected:

        ModifiersListAdapterTest()
                : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  adapter(tracktion_engine::getAudioTracks(*edit)[0]) {}

        void SetUp() override {

            tracktion_engine::getAudioTracks(*edit)[0]->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::LFO), -1,
                                                                                         nullptr);

            tracktion_engine::getAudioTracks(*edit)[0]->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::STEP), -1,
                                                                                         nullptr);

            tracktion_engine::getAudioTracks(*edit)[0]->getModifierList().insertModifier(juce::ValueTree(tracktion_engine::IDs::RANDOM), -1,
                                                                                         nullptr);

        }

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::ModifiersListAdapter adapter;

    };

    TEST_F(ModifiersListAdapterTest, size)
    {

        EXPECT_EQ(adapter.size(), 3);

    }

    TEST_F(ModifiersListAdapterTest, getItemNames)
    {

        EXPECT_EQ(adapter.getItemNames().size(), 3);
        EXPECT_EQ(adapter.getItemNames()[0], juce::String("LFO Modifier"));
        EXPECT_EQ(adapter.getItemNames()[1], juce::String("Step Modifier"));
        EXPECT_EQ(adapter.getItemNames()[2], juce::String("Random Modifier"));

    }

    TEST_F(ModifiersListAdapterTest, getItemAtIndex)
    {

        EXPECT_EQ(adapter.getItemAtIndex(0)->getName(), juce::String("LFO Modifier"));
        EXPECT_EQ(adapter.getItemAtIndex(1)->getName(),  juce::String("Step Modifier"));
        EXPECT_EQ(adapter.getItemAtIndex(2)->getName(), juce::String("Random Modifier"));
        EXPECT_EQ(adapter.getItemAtIndex(3), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(50), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(-1), nullptr);
        EXPECT_EQ(adapter.getItemAtIndex(-50), nullptr);

    }


}