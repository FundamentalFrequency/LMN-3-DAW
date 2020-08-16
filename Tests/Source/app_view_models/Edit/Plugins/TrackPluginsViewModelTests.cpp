#include <app_view_models/app_view_models.h>
#include "UnitTestCategories.h"

namespace AppViewModelsTests
{
    class TrackPluginsViewModelTests : public juce::UnitTest
    {

    public:

        class TrackPluginsViewModelListener : public app_view_models::TrackPluginsViewModel::Listener
        {

        public:

            int selectedIndex = 0;
            int selectedIndexChangeCount = 0;
            void selectedPluginIndexChanged(int newIndex) override {

                selectedIndexChangeCount++;
                selectedIndex = newIndex;

            };

            int pluginsChangeCount = 0;
            void pluginsChanged() override {

                pluginsChangeCount++;

            }

        };


        TrackPluginsViewModelTests() : juce::UnitTest("TrackPluginsViewModelTests class", UnitTestCategories::app_view_models) {}

        void runTest() override {


            tracktion_engine::Engine engine {"ENGINE"};
            app_view_models::MidiCommandManager midiCommandManager(engine);
            tracktion_engine::SelectionManager selectionManager(engine);

            auto singleTrackEdit = tracktion_engine::Edit::createSingleTrackEdit(engine);
            auto zeroPluginTrack = tracktion_engine::getAudioTracks(*singleTrackEdit).getUnchecked(0);
            zeroPluginTrack->pluginList.getPlugins().getUnchecked(0)->removeFromParent();
            zeroPluginTrack->pluginList.getPlugins().getUnchecked(0)->removeFromParent();
            app_view_models::TrackPluginsViewModel zeroPluginTrackPluginsViewModel(*zeroPluginTrack, midiCommandManager, selectionManager);


            beginTest("initial selected plugin index");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                auto track = tracktion_engine::getAudioTracks(*edit).getUnchecked(0);
                app_view_models::TrackPluginsViewModel trackPluginsViewModel(*track, midiCommandManager, selectionManager);
                expectEquals(trackPluginsViewModel.getSelectedPluginIndex(), 0, "initial selected plugin index is incorrect for multi plugin track");

                // remove a plugin so now there is only one plugin on the track
                track->pluginList.getPlugins().getUnchecked(0)->removeFromParent();
                app_view_models::TrackPluginsViewModel trackPluginsViewModel2(*track, midiCommandManager, selectionManager);
                expectEquals(trackPluginsViewModel2.getSelectedPluginIndex(), 0, "initial selected plugin index is incorrect for single plugin track");

                expectEquals(zeroPluginTrackPluginsViewModel.getSelectedPluginIndex(), -1, "initial selected plugin index is incorrect for track with 0 plugins");

            }


        }

    };

    static TrackPluginsViewModelTests trackPluginsViewModelTests;
}

