#include <app_models/app_models.h>
#include <gtest/gtest.h>
#include "BinaryData.h"

namespace AppModelsTests {

    class ThemeReaderTest : public ::testing::Test {
    protected:

        app_models::ThemeReader themeReader;

    };

    TEST_F(ThemeReaderTest, getThemes) {

        juce::ValueTree themesValueTree = themeReader.getThemes();
        EXPECT_EQ(themesValueTree.getType(), app_models::IDs::THEMES);
        EXPECT_EQ(themesValueTree.getNumChildren(), 2);

        juce::ValueTree gruvboxVT= themesValueTree.getChildWithProperty(app_models::IDs::name, juce::String("Gruvbox"));
        EXPECT_EQ(gruvboxVT.isValid(), true);
        EXPECT_EQ(gruvboxVT.getType(), app_models::IDs::THEME);
        EXPECT_EQ(gruvboxVT[app_models::IDs::name].toString(), juce::String("Gruvbox"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::backgroundColour].toString(), juce::String("ff1d2021"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::textColour].toString(),juce::String("ffebdbb2"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::colour1].toString(), juce::String("ff458588"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::colour2].toString(), juce::String("ff689d6a"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::colour3].toString(), juce::String("fffbf1c7"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::colour4].toString(), juce::String("ffcc241d"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::darkColour1].toString(), juce::String("ff224244"));
        EXPECT_EQ(gruvboxVT[app_models::IDs::disabledBackgroundColour].toString(), juce::String("df282828"));

        juce::ValueTree nightowlVT = themesValueTree.getChildWithProperty(app_models::IDs::name, juce::String("NightOwl"));
        EXPECT_EQ(nightowlVT.isValid(), true);
        EXPECT_EQ(nightowlVT.getType(), app_models::IDs::THEME);
        EXPECT_EQ(nightowlVT[app_models::IDs::name].toString(), juce::String("NightOwl"));
        EXPECT_EQ(nightowlVT[app_models::IDs::backgroundColour].toString(), juce::String("ff011627"));
        EXPECT_EQ(nightowlVT[app_models::IDs::textColour].toString(),juce::String("ffd6deeb"));
        EXPECT_EQ(nightowlVT[app_models::IDs::colour1].toString(), juce::String("ff82aaff"));
        EXPECT_EQ(nightowlVT[app_models::IDs::colour2].toString(), juce::String("ff22da6e"));
        EXPECT_EQ(nightowlVT[app_models::IDs::colour3].toString(), juce::String("ffffffff"));
        EXPECT_EQ(nightowlVT[app_models::IDs::colour4].toString(), juce::String("ffffcb8b"));
        EXPECT_EQ(nightowlVT[app_models::IDs::darkColour1].toString(), juce::String("ff224244"));
        EXPECT_EQ(nightowlVT[app_models::IDs::disabledBackgroundColour].toString(), juce::String("df011627"));

    }

}