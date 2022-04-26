namespace app_view_models {

namespace IDs {

const juce::Identifier STEP_SEQUENCER_STATE("STEP_SEQUENCER_VIEW_STATE");
const juce::Identifier selectedNoteIndex("selectedNoteIndex");
const juce::Identifier numberOfNotes("numberOfNotes");
const juce::Identifier notesPerMeasure("notesPerMeasure");

} // namespace IDs

class StepSequencerViewModel
    : public juce::ValueTree::Listener,
      public FlaggedAsyncUpdater,
      private tracktion_engine::TransportControl::Listener {
  public:
    StepSequencerViewModel(tracktion_engine::AudioTrack::Ptr t);
    ~StepSequencerViewModel();

    int getNumChannels();
    int getNumNotesPerChannel();
    int getMaximumNumberOfNotes();

    bool hasNoteAt(int channel, int noteIndex);

    void toggleNoteNumberAtSelectedIndex(int noteNumber);

    int noteNumberToChannel(int noteNumber);

    int getSelectedNoteIndex();
    int getNumberOfNotes();

    void incrementSelectedNoteIndex();
    void decrementSelectedNoteIndex();

    void incrementNumberOfNotes();
    void decrementNumberOfNotes();

    int getNotesPerMeasure();
    void incrementNotesPerMeasure();
    void decrementNotesPerMeasure();

    void clearNotesAtSelectedIndex();

    void play();
    void stop();

    class Listener {
      public:
        virtual ~Listener() = default;

        virtual void patternChanged(){};
        virtual void selectedNoteIndexChanged(int newIndex){};
        virtual void numberOfNotesChanged(int newNumberOfNotes){};
        virtual void notesPerMeasureChanged(int newNotesPerMeasure){};
    };

    void addListener(Listener *l);
    void removeListener(Listener *l);

  private:
    tracktion_engine::AudioTrack::Ptr track;
    tracktion_engine::MidiClip::Ptr midiClip;

    juce::ValueTree state;
    app_models::StepSequence stepSequence;

    double midiClipStart;
    double midiClipEnd;

    tracktion_engine::ConstrainedCachedValue<int> selectedNoteIndex;
    tracktion_engine::ConstrainedCachedValue<int> numberOfNotes;

    juce::ListenerList<Listener> listeners;

    // Async update markers
    bool shouldUpdatePattern = false;
    bool shouldUpdateSelectedNoteIndex = false;
    bool shouldUpdateNumberOfNotes = false;
    bool shouldUpdateNotesPerMeasure = false;

    juce::CachedValue<int> notesPerMeasure;
    juce::Array<int> notesPerMeasureOptions = juce::Array<int>({4, 8, 16});

    void handleAsyncUpdate() override;
    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    void generateMidiSequence();

    // used for transport changes
    void playbackContextChanged() override{};
    void autoSaveNow() override{};
    void setAllLevelMetersActive(bool) override{};
    void setVideoPosition(double time, bool forceJump) override;
    void startVideo() override{};
    void stopVideo() override{};

    static double floorToFraction(double number, double denominator = 1);
};

} // namespace app_view_models
