#include <gtest/gtest.h>
#include <juce_events/juce_events.h>

int main(int argc, char **argv) {
    juce::ScopedJuceInitialiser_GUI init;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}