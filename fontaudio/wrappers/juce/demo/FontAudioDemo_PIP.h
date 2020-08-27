/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.
 
 BEGIN_JUCE_PIP_METADATA
 
 name:             FontAudioDemo
 version:          1.0.0
 vendor:           fefanto
 website:          https://github.com/fefanto/fontaudio
 description:      Showcases widgets based on Fontaudio.
 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
 juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2017, linux_make, androidstudio, xcode_iphone
 moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1
 type:             Component
 mainClass:        FontAudioDemo
 useLocalCopy:     1
 
 END_JUCE_PIP_METADATA
 
 *******************************************************************************/
#pragma once

#include "FontAudioDemo_widgets.h"

#ifndef FONTAUDIO_MODULE_INCLUDED
#error "Please include fontaudio module in /wrappers/juce/module/fontaudio"
#include <pleaseincludefontaudiomodule>
#endif

//==============================================================================
struct FontAudioDemo : public Component
{
  FontAudioDemo()
  {

    setOpaque(true);
    addAndMakeVisible(&switchesDemo);
    addAndMakeVisible(&combosDemo);
    addAndMakeVisible(&rotarySlidersDemo);
    addAndMakeVisible(&linearSlidersDemo);
    addAndMakeVisible(&logosDemo);
    addAndMakeVisible(&mediaPlayerDemo);
    addAndMakeVisible(&genericToolbarDemo);
    addAndMakeVisible(&dawToolbarDemo);
    addAndMakeVisible(&dawToolbarDemo2);
    addAndMakeVisible(&trackControlsDemo);
    addAndMakeVisible(&distControlsDemo);
    addAndMakeVisible(&digitalClockDemo);

    switchesDemo.addControl(new SwitchButton(fontaudio::Powerswitch, fontaudio::Powerswitch, Colours::lightblue, Colours::black, Colours::grey));
    switchesDemo.addControl(new SwitchButton(fontaudio::RoundswitchOn, fontaudio::RoundswitchOff, Colours::lightblue.darker(), Colours::lightblue, Colours::grey));
    switchesDemo.addControl(new SwitchButton(fontaudio::VroundswitchOn, fontaudio::VroundswitchOff, Colours::lightblue.darker(), Colours::lightblue, Colours::grey));
    switchesDemo.addControl(new SwitchButton(fontaudio::SquareswitchOn, fontaudio::SquareswitchOff, Colours::lightblue.darker(), Colours::lightblue, Colours::grey));
    switchesDemo.addControl(new SwitchButton(fontaudio::VsquareswitchOn, fontaudio::VsquareswitchOff, Colours::lightblue.darker(), Colours::lightblue, Colours::grey));

    ComboBoxDemo *comboFilter = new ComboBoxDemo{"filter"};
    ComboBoxDemo *comboEnvelope = new ComboBoxDemo{"envelope"};
    ComboBoxDemo *comboArpeggiator = new ComboBoxDemo{"arp"};
    ComboBoxDemo *comboLfo = new ComboBoxDemo{"LFO"};

    comboFilter->addComboItem(fontaudio::FilterBypass, 1);
    comboFilter->addComboItem(fontaudio::FilterLowpass, 2);
    comboFilter->addComboItem(fontaudio::FilterHighpass, 3);
    comboFilter->addComboItem(fontaudio::FilterRezLowpass, 4);
    comboFilter->addComboItem(fontaudio::FilterRezHighpass, 5);
    comboFilter->addComboItem(fontaudio::FilterBandpass, 6);
    comboFilter->addComboItem(fontaudio::FilterNotch, 7);
    comboFilter->addComboItem(fontaudio::FilterShelvingHi, 8);
    comboFilter->addComboItem(fontaudio::FilterShelvingLo, 9);
    comboFilter->addComboItem(fontaudio::FilterBell, 10);

    comboEnvelope->addComboItem(fontaudio::Ar, 1);
    comboEnvelope->addComboItem(fontaudio::Adr, 2);
    comboEnvelope->addComboItem(fontaudio::Adsr, 3);
    comboEnvelope->addComboItem(fontaudio::Ahdsr, 4);

    comboArpeggiator->addComboItem(fontaudio::Arpup, 1);
    comboArpeggiator->addComboItem(fontaudio::Arpdown, 2);
    comboArpeggiator->addComboItem(fontaudio::Arpupdown, 3);
    comboArpeggiator->addComboItem(fontaudio::Arpdownup, 4);
    comboArpeggiator->addComboItem(fontaudio::Arpupandown, 5);
    comboArpeggiator->addComboItem(fontaudio::Arpdownandup, 6);
    comboArpeggiator->addComboItem(fontaudio::Arprandom, 7);
    comboArpeggiator->addComboItem(fontaudio::Arpplayorder, 8);
    comboArpeggiator->addComboItem(fontaudio::Arpchord, 9);

    comboLfo->addComboItem(fontaudio::Modsine, 1);
    comboLfo->addComboItem(fontaudio::Modsquare, 2);
    comboLfo->addComboItem(fontaudio::Modsh, 3);
    comboLfo->addComboItem(fontaudio::Modsawup, 4);
    comboLfo->addComboItem(fontaudio::Modsawdown, 5);
    comboLfo->addComboItem(fontaudio::Modtri, 6);
    comboLfo->addComboItem(fontaudio::Modrandom, 7);

    combosDemo.addControl(comboFilter);
    combosDemo.addControl(comboEnvelope);
    combosDemo.addControl(comboArpeggiator);
    combosDemo.addControl(comboLfo);

    rotarySlidersDemo.addControl(new RotarySlider(fontaudio::SliderRound1, Colours::lightblue));
    rotarySlidersDemo.addControl(new RotarySlider(fontaudio::SliderRound2, Colours::lightblue));
    rotarySlidersDemo.addControl(new RotarySlider(fontaudio::SliderRound3, Colours::lightblue));

    linearSlidersDemo.addControl(new LinearSlider(fontaudio::Sliderhandle1, Colours::lightblue));
    linearSlidersDemo.addControl(new LinearSlider(fontaudio::Sliderhandle2, Colours::lightblue));

    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoJuce, URL{"https://www.juce.com"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoAu, URL{"https://en.wikipedia.org/wiki/Audio_Units"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoFl, URL{"https://www.image-line.com/flstudio"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoAax, URL{"http://apps.avid.com/aax-portal/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoLv2, URL{"http://lv2plug.in/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoVst, URL{"https://www.steinberg.net/en/company/technologies/vst3.html"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoLive, URL{"https://www.ableton.com"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoCubase, URL{"https://new.steinberg.net"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoLadspa, URL{"https://www.ladspa.org/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoReaper, URL{"https://www.reaper.fm/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoReason, URL{"https://www.propellerheads.com/en/reason"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoRewire, URL{"https://www.propellerheads.com/developer/index.cfm?fuseaction=get_article&article=rewiretechinfo"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoRackext, URL{"https://www.propellerheads.com/developers"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoAudacity, URL{"https://www.audacityteam.org/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoAudiobus, URL{"https://audiob.us/"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoProtools, URL{"https://www.avid.com/pro-tools"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoWaveform, URL{"https://www.tracktion.com/products/waveform"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoStudioone, URL{"https://www.presonus.com/products/Studio-One"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoTracktion, URL{"https://www.tracktion.com/products/t7-daw"}));
    logosDemo.addControl(new FontaudioHyperlinkButton(fontaudio::LogoAbletonlink, URL{"https://www.ableton.com/en/link/"}));

    clockPanel = new DigitalClockDemoPanel();

    PushButton *playButton = new PushButton(fontaudio::Play, Colours::lightcoral, defaultDisabledColour);
    playButton->onClick = [this] { clockPanel->play(); };
    PushButton *pauseButton = new PushButton(fontaudio::Pause, Colours::lightcoral, defaultDisabledColour);
    pauseButton->onClick = [this] { clockPanel->pause(); };
    PushButton *stopButton = new PushButton(fontaudio::Stop, Colours::lightcoral, defaultDisabledColour);
    stopButton->onClick = [this] { clockPanel->stop(); };

    mediaPlayerDemo.addControl(new PushButton(fontaudio::Backward, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Rew, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Prev, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(playButton);
    mediaPlayerDemo.addControl(pauseButton);
    mediaPlayerDemo.addControl(stopButton);
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Next, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Ffwd, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Forward, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Repeat, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::RepeatOne, Colours::lightblue, defaultDisabledColour));
    mediaPlayerDemo.addControl(new PushButton(fontaudio::Shuffle, Colours::lightblue, defaultDisabledColour));

    genericToolbarDemo.addControl(new PushButton(fontaudio::Open, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Close, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Save, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Saveas, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Copy, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Paste, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Undo, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Redo, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::HExpand, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::VExpand, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Unlock, Colours::lightblue, defaultDisabledColour));
    genericToolbarDemo.addControl(new PushButton(fontaudio::Lock, Colours::lightblue, defaultDisabledColour));

    dawToolbarDemo.addControl(new PushButton(fontaudio::Automation2p, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Automation3p, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Automation4p, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Cpu, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Ram, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Diskio, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Loop, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Metronome, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Keyboard, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Waveform, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Duplicate, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::ArrowsHorz, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::ArrowsVert, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::PunchIn, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::PunchOut, Colours::lightblue, defaultDisabledColour));

    dawToolbarDemo.addControl(new PushButton(fontaudio::Cutter, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo.addControl(new PushButton(fontaudio::Pen, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Eraser, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Timeselect, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Pointer, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Zoomin, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Zoomout, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Random1dice, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Random2dice, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::Scissors, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::CaretUp, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::CaretDown, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::CaretLeft, Colours::lightblue, defaultDisabledColour));
    dawToolbarDemo2.addControl(new PushButton(fontaudio::CaretRight, Colours::lightblue, defaultDisabledColour));

    trackControlsDemo.addControl(new PushButton(fontaudio::Armrecording, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::Mute, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::Solo, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::Mono, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::Stereo, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::Phase, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::PresetA, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::PresetB, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::PresetAb, Colours::lightblue, defaultDisabledColour));
    trackControlsDemo.addControl(new PushButton(fontaudio::PresetBa, Colours::lightblue, defaultDisabledColour));

    distControlsDemo.addControl(new PushButton(fontaudio::Foldback, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Hardclip, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Hardclipcurve, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Softclip, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Softclipcurve, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Speaker, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Headphones, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Bluetooth, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Thunderbolt, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Usb, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Midiplug, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Xlrplug, Colours::lightblue, defaultDisabledColour));
    distControlsDemo.addControl(new PushButton(fontaudio::Drumpad, Colours::lightblue, defaultDisabledColour));

    digitalClockDemo.addControl(clockPanel);
    setSize(1400, 600);
  }

  void paint(Graphics &g) override
  {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
  }

  void resized() override
  {
    Rectangle<float> bounds = getLocalBounds().toFloat();
    float rowSize = bounds.getHeight() * 0.1f;
    float colSizeOneThird = bounds.getWidth() * 0.33f;

    Rectangle<float> thisRow = bounds.removeFromTop(rowSize);
    switchesDemo.setBounds(thisRow.removeFromLeft(colSizeOneThird).toNearestInt());
    combosDemo.setBounds(thisRow.toNearestInt());

    thisRow = bounds.removeFromTop(rowSize);
    rotarySlidersDemo.setBounds(thisRow.removeFromLeft(colSizeOneThird).toNearestInt());
    linearSlidersDemo.setBounds(thisRow.toNearestInt());

    logosDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    mediaPlayerDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    genericToolbarDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    dawToolbarDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    dawToolbarDemo2.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    trackControlsDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    distControlsDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
    digitalClockDemo.setBounds((thisRow = bounds.removeFromTop(rowSize)).toNearestInt());
  }

  FlexBoxDemoPanel switchesDemo{"switches", FlexBox::Direction::row};
  FlexBoxDemoPanel combosDemo{"combos", FlexBox::Direction::row};
  FlexBoxDemoPanel rotarySlidersDemo{"rotary sliders", FlexBox::Direction::row};
  FlexBoxDemoPanel linearSlidersDemo{"linear sliders", FlexBox::Direction::row};
  FlexBoxDemoPanel logosDemo{"logos", FlexBox::Direction::row};
  FlexBoxDemoPanel mediaPlayerDemo{"media player", FlexBox::Direction::row};
  FlexBoxDemoPanel genericToolbarDemo{"generic tools", FlexBox::Direction::row};
  FlexBoxDemoPanel dawToolbarDemo{"DAW tools (I)", FlexBox::Direction::row};
  FlexBoxDemoPanel dawToolbarDemo2{"DAW tools (II)", FlexBox::Direction::row};
  FlexBoxDemoPanel trackControlsDemo{"Track & Presets", FlexBox::Direction::row};
  FlexBoxDemoPanel distControlsDemo{"Distortion & Misc.", FlexBox::Direction::row};
  FlexBoxDemoPanel digitalClockDemo{"Digital clock / Timecode", FlexBox::Direction::row};
  DigitalClockDemoPanel *clockPanel;
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FontAudioDemo)
};
