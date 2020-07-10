namespace app_models {

    class PresetSlotList : public tracktion_engine::ValueTreeObjectList<PresetSlot> {

    public:

        PresetSlotList(const juce::ValueTree &v);

        ~PresetSlotList();

        bool isSuitableType(const juce::ValueTree &v) const override;

        PresetSlot *createNewObject(const juce::ValueTree &v) override;

        void deleteObject(PresetSlot *ps) override;

        void newObjectAdded(PresetSlot *ps) override;

        void objectRemoved(PresetSlot *ps) override;

        void objectOrderChanged() override;

    };

}

