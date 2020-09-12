#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockTempoSettingsViewModelListener.h"
namespace AppViewModelsTests {


    class TempoSettingsViewModelTest : public ::testing::Test {
    protected:

        TempoSettingsViewModelTest()
                : edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  viewModel(*edit) {}

        void SetUp() override {

            // flush any pending updates
            viewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine{"ENGINE"};
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::TempoSettingsViewModel viewModel;

    };

    TEST_F(TempoSettingsViewModelTest, setBpm)
    {

        MockTempoSettingsViewModelListener listener;

        // called once when added listener added
        EXPECT_CALL(listener, bpmChanged(120))
                .Times(1);

        EXPECT_CALL(listener, bpmChanged(80))
                .Times(1);

        viewModel.addListener(&listener);


        viewModel.setBpm(80);
        viewModel.handleUpdateNowIfNeeded();


    }

    using ::testing::_;
    TEST_F(TempoSettingsViewModelTest, setClickTrackGain)
    {

        MockTempoSettingsViewModelListener listener;

        // called once when added listener added
        EXPECT_CALL(listener, clickTrackGainChanged(_))
        .Times(1);

        EXPECT_CALL(listener, clickTrackGainChanged(0.5))
        .Times(1);

        viewModel.addListener(&listener);


        viewModel.setClickTrackGain(0.5);
        viewModel.handleUpdateNowIfNeeded();


    }

}