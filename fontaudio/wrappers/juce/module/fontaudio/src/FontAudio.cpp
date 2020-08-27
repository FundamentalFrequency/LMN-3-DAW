namespace fontaudio
{
  
  IconHelper::IconHelper()
  {
  }
  
  IconHelper::~IconHelper()
  {
  }
  
  RenderedIcon IconHelper::getIcon(IconName icon, float size, juce::Colour colour, float scaleFactor)
  {
    int scaledSize = int(size * scaleFactor);
    
    String identifier = juce::String(icon + "@" + String(scaledSize) + "@" + colour.toString());
    int64 hash = identifier.hashCode64();
    Image canvas = juce::ImageCache::getFromHashCode(hash);
    if (canvas.isValid())
      return canvas;
    
    Font FontAudio = getFont((float)scaledSize);
    scaledSize = std::max(FontAudio.getStringWidth(icon), scaledSize);
    
    canvas = Image(Image::PixelFormat::ARGB, scaledSize, scaledSize, true);
    Graphics g(canvas);
    g.setColour(colour);
    g.setFont(FontAudio);
    g.drawText(icon, 0, 0, scaledSize, scaledSize, Justification::centred, true);
    juce::ImageCache::addImageToCache(canvas, hash);
    return canvas;
  }
  
  RenderedIcon IconHelper::getRotatedIcon(IconName icon, float size, juce::Colour colour, float iconRotation, float scaleFactor)
  {
    int scaledSize = int(size * scaleFactor);
    String identifier = String(icon + "@" + String(scaledSize) + "@" + colour.toString() + "@" + String(iconRotation) + "@");
    int64 hash = identifier.hashCode64();
    Image canvas = juce::ImageCache::getFromHashCode(hash);
    if (canvas.isValid())
      return canvas;
    
    RenderedIcon renderdIcon = getIcon(icon, size, colour, scaleFactor);
    canvas = Image(Image::PixelFormat::ARGB, renderdIcon.getWidth(), renderdIcon.getHeight(), true);
    Graphics g(canvas);
    g.drawImageTransformed(renderdIcon, AffineTransform::rotation(-(float_Pi * iconRotation), renderdIcon.getWidth() * 0.5f, renderdIcon.getHeight() * 0.5f));
    juce::ImageCache::addImageToCache(canvas, hash);
    return canvas;
  }
  
  void IconHelper::drawAt(juce::Graphics &g, RenderedIcon icon, int x, int y, float scaleFactor)
  {
    int w = icon.getWidth();
    int h = icon.getHeight();
    g.drawImage(icon,
                x, y,
                (int)(w / scaleFactor), (int)(h / scaleFactor),
                0, 0,
                w, h,
                false);
  }
  
  void IconHelper::drawCenterdAt(juce::Graphics &g, RenderedIcon icon, Rectangle<int> r, float scaleFactor)
  {
    float iconWidth = icon.getWidth() / scaleFactor;
    float iconHeight = icon.getHeight() / scaleFactor;
    
    int x = r.getX() + (int)((r.getWidth() * 0.5f) - (iconWidth * 0.5f));
    int y = r.getY() + (int)((r.getHeight() * 0.5f) - (iconHeight * 0.5f));
    g.drawImage(icon, x, y, (int)iconWidth, (int)iconHeight, 0, 0, icon.getWidth(), icon.getWidth());
  }
  
  juce::Font IconHelper::getFont()
  {
    static Font FontAudioFont(FontAudio_ptr);
    return FontAudioFont;
  }
  
  juce::Font IconHelper::getFont(float size)
  {
    juce::Font font = getFont();
    font.setHeight(size);
    return font;
  }
  
  void IconHelper::drawAt(juce::Graphics &g, IconName icon, float size, juce::Colour colour, int x, int y, float scaleFactor)
  {
    drawAt(g, getIcon(icon, size, colour, scaleFactor), x, y, scaleFactor);
  }
  
  void IconHelper::drawAt(juce::Graphics &g, IconName icon, float size, juce::Colour colour, int x, int y)
  {
    drawAt(g, getIcon(icon, size, colour, g.getInternalContext().getPhysicalPixelScaleFactor()), x, y, g.getInternalContext().getPhysicalPixelScaleFactor());
  }
  
  void IconHelper::drawCenterd(juce::Graphics &g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float scaleFactor)
  {
    drawCenterdAt(g, getIcon(icon, size, colour, scaleFactor), r, scaleFactor);
  }
  
  void IconHelper::drawCenterd(juce::Graphics &g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r)
  {
    drawCenterdAt(g, getIcon(icon, size, colour, g.getInternalContext().getPhysicalPixelScaleFactor()), r, g.getInternalContext().getPhysicalPixelScaleFactor());
  }
  
  void IconHelper::drawAtRotated(juce::Graphics &g, IconName icon, float size, juce::Colour colour, int x, int y, float rotation, float scaleFactor)
  {
    drawAt(g, getRotatedIcon(icon, size, colour, rotation, scaleFactor), x, y, scaleFactor);
  }
  
  void IconHelper::drawAtRotated(juce::Graphics &g, IconName icon, float size, juce::Colour colour, int x, int y, float rotation)
  {
    drawAt(g, getRotatedIcon(icon, size, colour, rotation, g.getInternalContext().getPhysicalPixelScaleFactor()), x, y, g.getInternalContext().getPhysicalPixelScaleFactor());
  }
  
  void IconHelper::drawCenterdRotated(juce::Graphics &g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation, float scaleFactor)
  {
    drawCenterdAt(g, getRotatedIcon(icon, size, colour, rotation, scaleFactor), r, scaleFactor);
  }
  
  void IconHelper::drawCenterdRotated(juce::Graphics &g, IconName icon, float size, juce::Colour colour, juce::Rectangle<int> r, float rotation)
  {
    drawCenterdAt(g, getRotatedIcon(icon, size, colour, rotation, g.getInternalContext().getPhysicalPixelScaleFactor()), r, g.getInternalContext().getPhysicalPixelScaleFactor());
  }
  
} // end namespace fontaudio
