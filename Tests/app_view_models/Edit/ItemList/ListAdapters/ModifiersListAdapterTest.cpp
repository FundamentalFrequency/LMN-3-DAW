#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>

namespace AppViewModelsTests {

class ModifiersListAdapterTest : public ::testing::Test {
  protected:
    ModifiersListAdapterTest()
        : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
          adapter(tracktion_engine::getAudioTracks(*edit)[0]) {}

    void SetUp() override {

        auto modifier1 =
            tracktion_engine::getAudioTracks(*edit)[0]
                ->getModifierList()
                .insertModifier(juce::ValueTree(tracktion_engine::IDs::LFO), -1,
                                nullptr);
        auto pluginParameter = tracktion_engine::getAudioTracks(*edit)[0]
                                   ->getVolumePlugin()
                                   ->volParam;
        pluginParameter->addModifier(*modifier1);

        auto modifier2 =
            tracktion_engine::getAudioTracks(*edit)[0]
                ->getModifierList()
                .insertModifier(juce::ValueTree(tracktion_engine::IDs::STEP),
                                -1, nullptr);
        auto pluginParameter2 = tracktion_engine::getAudioTracks(*edit)[0]
                                    ->getVolumePlugin()
                                    ->panParam;
        pluginParameter2->addModifier(*modifier2);

        auto modifier3 =
            tracktion_engine::getAudioTracks(*edit)[0]
                ->getModifierList()
                .insertModifier(juce::ValueTree(tracktion_engine::IDs::RANDOM),
                                -1, nullptr);
        auto pluginParameter3 = tracktion_engine::getAudioTracks(*edit)[0]
                                    ->getVolumePlugin()
                                    ->panParam;
        pluginParameter3->addModifier(*modifier3);
    }

    tracktion_engine::Engine engine{"ENGINE"};
    std::unique_ptr<tracktion_engine::Edit> edit;
    app_view_models::ModifiersListAdapter adapter;
};

TEST_F(ModifiersListAdapterTest, size) { EXPECT_EQ(adapter.size(), 3); }

TEST_F(ModifiersListAdapterTest, getItemNames) {

    EXPECT_EQ(adapter.getItemNames().size(), 3);
    EXPECT_EQ(adapter.getItemNames()[0],
              juce::String("LFO>Volume & Pan:Volume"));
    EXPECT_EQ(adapter.getItemNames()[1], juce::String("Step>Volume & Pan:Pan"));
    EXPECT_EQ(adapter.getItemNames()[2],
              juce::String("Random>Volume & Pan:Pan"));
}

TEST_F(ModifiersListAdapterTest, getItemAtIndex) {

    EXPECT_EQ(adapter.getItemAtIndex(0)->getName(),
              juce::String("LFO Modifier"));
    EXPECT_EQ(adapter.getItemAtIndex(1)->getName(),
              juce::String("Step Modifier"));
    EXPECT_EQ(adapter.getItemAtIndex(2)->getName(),
              juce::String("Random Modifier"));
    EXPECT_EQ(adapter.getItemAtIndex(3), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(50), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-1), nullptr);
    EXPECT_EQ(adapter.getItemAtIndex(-50), nullptr);
}

} // namespace AppViewModelsTests