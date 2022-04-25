#pragma once
#include "AppLookAndFeel.h"
#include "MixerTableListBoxModel.h"
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
class MixerView : public juce::Component,
                  public app_services::MidiCommandManager::Listener,
                  public app_view_models::EditItemListViewModel::Listener,
                  public app_view_models::ItemListState::Listener {
  public:
    MixerView(tracktion_engine::Edit &e, app_services::MidiCommandManager &mcm);
    ~MixerView();
    void paint(juce::Graphics &g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder1ButtonReleased() override;

    void encoder3Increased() override;
    void encoder3Decreased() override;

    void encoder4Increased() override;
    void encoder4Decreased() override;

    void encoder3ButtonReleased() override;
    void encoder4ButtonReleased() override;

    // ItemListState listener methods
    void selectedIndexChanged(int newIndex) override;

    // EditItemListViewModel listener methods
    void itemsChanged() override;

  private:
    tracktion_engine::Edit &edit;
    app_services::MidiCommandManager &midiCommandManager;
    app_view_models::MixerViewModel viewModel;
    std::unique_ptr<MixerTableListBoxModel> tableListModel;
    juce::TableListBox tableListBox;

    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerView)
};
