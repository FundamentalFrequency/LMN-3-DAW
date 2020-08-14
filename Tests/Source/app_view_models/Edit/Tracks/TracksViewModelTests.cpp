#include <app_view_models/app_view_models.h>
#include "UnitTestCategories.h"

namespace AppViewModelsTests
{
    class TracksViewModelTests : public juce::UnitTest
    {

    public:

        TracksViewModelTests() : juce::UnitTest("TracksViewModelTests class", UnitTestCategories::app_view_models) {}

        void runTest() override {


            tracktion_engine::Engine engine {"ENGINE"};

            beginTest("initial test");
            {

                auto edit = tracktion_engine::Edit::createSingleTrackEdit(engine);
                app_models::TracksViewState tracksViewState(*edit);
                app_view_models::TracksViewModel tracksViewModel(tracksViewState);


            }


        }

    };

    static TracksViewModelTests tracksViewModelTests;
}

