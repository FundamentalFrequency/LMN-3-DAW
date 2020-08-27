#ifndef __FONTAUDIO_HEADER__
#define __FONTAUDIO_HEADER__

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               fontaudio
  vendor:           fefanto
  version:          1.0.0
  name:             Font Audio
  description:      Font Audio is an icon font for audio UIs.
  website:          https://github.com/fefanto/fontaudio
  license:          The MIT License (MIT)

  dependencies:     juce_core juce_graphics

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/
#define FONTAUDIO_MODULE_INCLUDED


#if JUCE_LITTLE_ENDIAN && !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__
#endif

#if JUCE_MAC
#define __MACOSX_CORE__
#endif

#if JUCE_MSVC
#pragma warning(push)
#pragma warning(disable : 4127 4702 4244 4305 4100 4996 4309)
#endif



#include "juce_core/juce_core.h"
#include "juce_graphics/juce_graphics.h"
using namespace juce;

#include "data/FontAudioData.h"
#include "data/Icons.h"

#include "src/FontAudio.h"

#endif // __FONTAUDIO_HEADER__

