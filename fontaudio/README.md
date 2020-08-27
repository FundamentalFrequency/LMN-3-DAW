# Fontaudio - icon toolkit for audio developers

> [202006] Version 1.1 - fixed icons appearance on windows (and hopefully linux).

> [201907] Version 1.0

> to leave feedback use issues on this repo, hit [@fefanto](https://twitter.com/fefanto) on twitter, or drop a me a [mail](mailto:fefanto@gmail.com)

## The Problem

You are writing your plugin suite (DSP test, DAW experiment or anything related to audio software) and before committing to a full time UI designer you'd like to avoid the "reinvent-the-UI-wheel" sindrome and use something free and tailored to your needs.

Your first stop is maybe the awesome ... [fontawesome](https://fontawesome.com/), and if you're programming in juce its equally awesome [juce wrapper](https://github.com/danlin/danlin_modules).

Lots of stuff is missing tough: mainstream icons sets may have your media player icons and some more random usable items, but everything super-duper-audio-specific like filters, arpeggiator types, LFO types, DAW toolbar icons are nowhere to be found in a consistent package. Also searching around you see incredible svg icon set projects (e.g. like [this](https://thenounproject.com/)) but information is sparse and even your scratch UIs are time consuming to cobble up.

## Enter FontAudio

This Icon set wants to be the one-stop-free-toolkit for Audio Software Related icons.

Its goal is:

- to help You out with your Time-to-Demo or Time-to-Product for your plugin or DAW.
- to be a consistent and up-to-date source for basic audio related Icons and artwork.
- to give you the joy of drawing the UI for a filter type icon or a rotary slider with just a couple of lines of code.

<h1><img src="https://github.com/fefanto/fontaudio/blob/master/screenshots/fad-screenshot.png?raw=true" alt="FontAudio demo screenshot" width="120%"></h1>

## License

**Icons — [CC BY 4.0 License](https://creativecommons.org/licenses/by/4.0/)**: applies to all icons packaged as .svg and .js file types.

**Fonts — [SIL OFL 1.1 License](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL)**: applies to all icons packaged as web and desktop font files.

**Code — [MIT License](https://opensource.org/licenses/MIT)**: applies to all non-font and non-icon files.

**Attribution** : Attribution is required by MIT, SIL OFL, and CC BY licenses. here's a copyright notice you can include in your product licenses file where you list stuff you've used.:

```

- fontaudio by @fefanto - https://github.com/fefanto/fontaudio
- license : https://github.com/fefanto/fontaudio/blob/master/README.md#license
  (Icons: CC BY 4.0, Fonts: SIL OFL 1.1, Code: MIT License)

```

**NOTE** : All logos and brand references are trademarks of their respective owners.
The use of these trademarks does not indicate endorsement of the trademark holder by fontaudio, nor vice versa. _Please do not use brand logos for any purpose except
to represent the company, product, or service to which they refer._

**NOTE** : I tried to design icons myself as much as possible and use logos that could be of interest to the audio developer. If any imagery constituting Your intellectual property or trademark cannot be included here just drop me a line (contacts on top of this file).

## Content

- **./font** : all the icon set standard formats (.ttf etc.)
- **./scripts** : js scripts for (1) creating the juce module binary data and icon names and (2) cleaning up the SVG files before they are stuffed in the font.
- **./svgs** : svg files (just fork, add your own and rebuild)
- **./svgs-refs** : svg files reference frames: these are used to design the icons within a base shape to keep a consistent "mass". Possibly use those as references for your custom svgs.
- **./wrappers/juce/module** : juce module
- **./wrappers/juce/demo** : juce demo [PIP](https://forum.juce.com/t/what-is-a-pip/26821)
- **./screenshots** : some screenshots (got no dedicated website yet)

## Dependencies

- node/yarn (node 8.10 and yarn 1.13.0 used for this 1.0 release)
  - [icon-font-generator](https://www.npmjs.com/package/icon-font-generator)
  - [svgo](https://github.com/svg/svgo)
- Juce - if you want to build the juce based demo (currently working with [Juce 5.4.4](https://github.com/WeAreROLI/JUCE/releases/tag/5.4.4))

## Building the font

_if you don't have any icons to add, just use the font in ./font or using its wrappers, otherwise..._

- run yarn
- design your custom svgs and add new svgs to /svgs folder
- run _yarn build:all_ (see package.json for the internal commands)

**NOTE**: the icon-font-generator node package I'm using does not play nice with svg translations/rotations (not that I think it should ... it's fair to have clean and lean paths before using them): _all paths flattened please!_ 😉

**NOTE**: currently developed on a mac - please leave feedback if you find trouble using this on windows/linux. Will try to make this truly cross platform.

## Building the Juce demo

- Drag the file _./wrappers/juce/demo/FontAudioDemo_PIP.h_ over your projucer (currently tested with juce 5.4.3 and 5.4.4)
- save your new projucer project somewhere (projucer command is : CMD+P)
- go to the projucer modules pane and select _"Add module from specified folder.."_ then select _./wrappers/juce/module/fontaudio_
- open your projucer preferred exporter and launch the demo

<h1><img src="https://github.com/fefanto/fontaudio/blob/master/screenshots/fad-screenshot-demo.png?raw=true" alt="FontAudio demo screenshot" width="100%"></h1>

## Using the Juce module

Once the Juce FontAudio module is successfully added in your project, the paradigm used comes from Juce's [SharedResourcePtr](https://docs.juce.com/master/classSharedResourcePointer.html). There's a _IconHelper_ class containing the font in binary code plus all the methods to draw the icons as Juce Images. (Thanks [Danlin](https://github.com/danlin) the class is mostly ported from your code, minus the Singleton thing).
All you have to do is to declare a class member in every class that's gonna use the font:

```
SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
```

Juce SharedResourcePtr will then take care of constructing it only once and refcounting its use across your project

```
// EXAMPLE I : In a LookAndFeel Class
class FontaudioLookAndFeel : public LookAndFeel_V4
{
private:
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
public:
  Font getComboBoxFont(ComboBox &) override
  {
    return sharedFontAudio->getFont(defaultFontAudioSize);
  }
  ...
}

// EXAMPLE II : In a button paint() method using drawText

  void paint(Graphics &g) override
  {
    fontaudio::IconName offIcon =fontaudio::RoundswitchOff;
    fontaudio::IconName onIcon = fontaudio::RoundswitchOn;
    g.setFont(sharedFontAudio->getFont(getHeight() * 0.8f));
    g.drawFittedText(getToggleState() ? onIcon : offIcon, getLocalBounds(), Justification::centred, 1, 1);
  }
```

## Contributing

- All feedback is welcome. Contacts are on top of this file.
- Pull requests with new svg icons added in ./svgs folder are welcome. Keep in mind the goal of this package is to contain all possible Audio-Software-Related icons, but these icons will need to have some minimal general interest and usability. This is where You and I may argue but I'm looking forward to clear my own mind on this with Your very welcome help. See below for types of icons i plan to include in the future and if you want to contribute please do.
- Design related feedback is _very_ welcome : I am NOT a designer and I tried to give this icon set a minimal consistence being well aware that the work is _very much_ improvable. For reference I used some 256x256 svg files I made with the goal of having a consistent "mass" while preserving the natural difference in icon shapes. You can find them at _./svgs-refs_.

## Roadmap::Tooling

_Stuff I intend to go forward with goes here - help is welcome._

- public yarn/npm package for web projects :
- other wrappers? for the web ? wdl-ol / llv2? fontaudio is also on iPlug2 see [here](https://www.patreon.com/posts/30368442).

## Roadmap::Next Icons

_Icons that I more or less think to be useful and get queued go here_

- Drum Sampler Icons : kick, hat, cymbal etc. In more than one form maybe.
- Notation Software Icons : all music notation icons that maybe useful to someone making a music scoring software. 

## Roadmap::Random Icon Ideas

_"maybe" icons go here ... feedback welcome on icons to include and also on how to design them._

_NOTE: not sure yet on how wide I want this package to be. E.g.: all analog "spice" blocks (opamps, resistors, diodes) may be considered as audio related since lots of plugins are modeling analog circuitry modeled ... But still I'm not that convinced to include them: too ambiguous and wide a topic, plus those are not for audio only..._

- spdif/TRS
- fade in/fade out
- audio formats: wav,mp3,aac,vorbis,aiff
- logos : recycle/remote
- send, return
- notes!!! quartes - octaves - triplets etc
- time signatures: 5/4,4/4,3/4,2/4,6/8,12/8
- db/oct : 6,12,18,24,48,96
- linear,exponential
- audio brands (there's a kvr post soewhere naming audio brands in order of "web reputation")
- review plugin types to see if some icons type arise -> delay / modulation / compression / reverb / distortion
- review synth types as well: additive, subtractive, FM, granular, wavetable, phase distortion etc.
- block diagram (opamp etc)
- more waveforms (fading in/out)
- more things distortion related (there's a "corrosion" plugin from sinevibes listing some funky distortion types :exponential, soft clip, hard clip, triangle clip, triangle foldback, single foldback, multi foldback, sine foldback, sine shred ... get some ideas from there.
