#pragma once
#include <gmock/gmock.h>
#include <app_models/app_models.h>

class MockThemeListener : public app_models::Themes::Listener
{
public:
    MOCK_METHOD(void, currentThemeChanged, (app_models::Theme *newTheme), (override));
};

