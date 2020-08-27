/*
 ==============================================================================
 
 FontAudio.h
 Created: 13 Jul 2014 12:19:09pm
 Original Author:  Daniel Lindenfelser
 
 Mods(fefanto - 2019-07-..) : removed singleton in favour of SharedResourcePointer<FontAudio>
 Usage :
 
 declare a class Member...
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
 ... wherever you want to use the class below
 
 The FontAudio_ptr member below will be constructed once and its owner class will be
 refcounted thanks to the SharedResourcePointer Magic
 
 ==============================================================================
 */

#pragma once

namespace fontaudio
{
  
  typedef juce::Image RenderedIcon;
  
  class IconHelper
  {
  public:
    IconHelper();
    virtual ~IconHelper();
    
    RenderedIcon getIcon(IconName icon, float size, juce::Colour colour, float scaleFactor = 1.0f);
    RenderedIcon getRotatedIcon(IconName icon, float size, juce::Colour colour, float iconRotation, float scaleFactor = 1.0f);
    
    void drawAt(juce::Graphics & g, RenderedIcon icon, int x, int y, float scaleFactor = 1.0f);
    void drawCenterdAt(juce::Graphics & g, RenderedIcon icon, juce::Rectangle<int> r, float scaleFactor = 1.0f);
    
    juce::Font getFont();
    juce::Font getFont(float size);
    
    void drawAt(juce::Graphics & g, IconName icon, float size, juce::Colour colour, int x, int y, float scaleFactor);
    void drawCenterd(juce::Graphics & g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float scaleFactor);
    
    void drawAt(juce::Graphics & g, IconName icon, float size, juce::Colour colour, int x, int y);
    void drawCenterd(juce::Graphics & g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r);
    
    void drawAtRotated(juce::Graphics & g, IconName icon, float size, juce::Colour colour, int x, int y, float rotation, float scaleFactor);
    void drawCenterdRotated(juce::Graphics & g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation, float scaleFactor);
    
    void drawAtRotated(juce::Graphics & g, IconName icon, float size, juce::Colour colour, int x, int y, float rotation);
    void drawCenterdRotated(juce::Graphics & g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation);
    
  private:
    juce::Typeface::Ptr FontAudio_ptr = juce::Typeface::createSystemTypefaceFor(FontAudioData::FontAudiowebfont_ttf, FontAudioData::FontAudiowebfont_ttfSize);
  };
  
} // end namespace fontaudio
