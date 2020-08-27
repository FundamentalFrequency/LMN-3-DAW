
#pragma once


const Colour defaultOffColour = Colours::lightblue;
const Colour defaultOnColour = Colours::lightblue;
const Colour defaultDisabledColour = Colours::darkgrey;
const int defaultFontAudioSize = 18;



/*
 ==============================================================================
 lookandfeel that goes for fontaudio for possibly all getXYZFont methods
 ==============================================================================
 */
class FontaudioLookAndFeel : public LookAndFeel_V4
{
private:
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
public:
  Font getComboBoxFont(ComboBox &) override
  {
    return sharedFontAudio->getFont(defaultFontAudioSize);
  }
  
//  void positionComboBoxText (ComboBox& box, Label& label) override
//  {
//    label.setBounds (1, 1,
//                     box.getWidth() - 20,
//                     box.getHeight() - 2);
//
//    label.setFont (getComboBoxFont (box));
//    label.setJustificationType(Justification::horizontallyCentred);
//  }
  
  Font getLabelFont(Label &) override
  {
    return sharedFontAudio->getFont(defaultFontAudioSize);
  }
  
  Font getPopupMenuFont() override
  {
    return sharedFontAudio->getFont(defaultFontAudioSize);
  }
  
  Font getTextButtonFont(TextButton &, int buttonHeight) override
  {
    return sharedFontAudio->getFont(defaultFontAudioSize);
  }
};

/*
 ==============================================================================
 Container component for flex box based demo
 ==============================================================================
 */

class FlexBoxDemoPanel : public Component
{
  
public:
  FlexBoxDemoPanel(const String &name,
                   FlexBox::Direction direction) : Component(name),
  dirty_(false)
  {
    masterBox_.alignItems = FlexBox::AlignItems::stretch;
    masterBox_.alignContent = FlexBox::AlignContent::stretch;
    masterBox_.flexWrap = FlexBox::Wrap::noWrap;
    masterBox_.justifyContent = FlexBox::JustifyContent::flexEnd;
    masterBox_.flexDirection = direction;
    
    Label* panelLabel = new Label(name, name);
    panelLabel->setJustificationType(Justification::topLeft);
    addControl(panelLabel);
  };
  
  virtual ~FlexBoxDemoPanel(){};
  
  void clear()
  {
    masterBox_.items.clear();
  }
  
  void addControl(Component *control, float flex = 1.0f)
  {
    jassert(control != nullptr);
    controls_.add(control);
    flexes_.add(flex);
    this->addAndMakeVisible(control);
    dirty_ = true;
  }
  
  void resized() override
  {
    
    Rectangle<float> bounds = getLocalBounds().reduced(2).toFloat();
    if (dirty_.load())
      clear();
    jassert(flexes_.size() == controls_.size());
    FlexItem::Margin mrgn{0.0, 0.0, 0.0, 0.0};
    
    for (int i = 0; i < controls_.size(); i++)
    {
      masterBox_.items.add(FlexItem(1, 1).withFlex(flexes_[i]).withMargin(mrgn));
      auto &flexItem = masterBox_.items.getReference(masterBox_.items.size() - 1);
      flexItem.associatedComponent = controls_[i];
    }
    masterBox_.performLayout(bounds);
  }
  
  void paint(Graphics &g) override
  {
    Rectangle<float> bounds = getLocalBounds().reduced(2).toFloat();
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(0, 0, bounds.getWidth(), bounds.getHeight(), 5.0f, 2.0f);
  }
  
private:
  OwnedArray<Component> controls_;
  Array<float> flexes_;
  
  FlexBox masterBox_;
  std::atomic_bool dirty_;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlexBoxDemoPanel)
};


/*
 ==============================================================================
 Hyperlink button using fontaudio for rendering text
 ==============================================================================
 */

class FontaudioHyperlinkButton : public HyperlinkButton
{
private:
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  
public:
  FontaudioHyperlinkButton(const String &linkText,
                           const URL &linkURL) : HyperlinkButton(linkText, linkURL)
  {
    setFont(sharedFontAudio->getFont(), true);
    setColour(textColourId, Colours::lightblue);
  }
};

/*
 ==============================================================================
 Toggle button displaying a fontaudio icon based on its state
 ==============================================================================
 */

class SwitchButton : public TextButton
{
public:
  SwitchButton(fontaudio::IconName onIcon, fontaudio::IconName offIcon, Colour onColour, Colour offColour, Colour disabledColour) : onColour(onColour),
  offColour(offColour),
  disabledColour(disabledColour),
  offIcon(offIcon),
  onIcon(onIcon)
  {
    setClickingTogglesState(true);
    setTriggeredOnMouseDown(true);
  };
  
  virtual ~SwitchButton(){};
  
  void paint(Graphics &g) override
  {
    g.setFont(sharedFontAudio->getFont(getHeight() * 0.8f));
    Colour baseColour = getToggleState() ? onColour : offColour;
    g.setColour(isEnabled() ? (isMouseOver() ? baseColour.brighter() : baseColour) : disabledColour);
    g.drawFittedText(getToggleState() ? onIcon : offIcon, getLocalBounds(), Justification::centred, 1, 1);
  }
  
private:
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  Colour onColour, offColour, disabledColour;
  fontaudio::IconName offIcon, onIcon;
};

/*
 ==============================================================================
 Text button displaying a fontaudio icon
 ==============================================================================
 */
class PushButton : public TextButton
{
public:
  PushButton(fontaudio::IconName icon, Colour textColour, Colour disabledColour) : textColour(textColour),
  disabledColour(disabledColour),
  icon(icon)
  {
    setClickingTogglesState(false);
    setTriggeredOnMouseDown(true);
  };
  
  virtual ~PushButton(){};
  
  void paint(Graphics &g) override
  {
    g.setFont(sharedFontAudio->getFont(getHeight() * 0.8f));
    g.setColour(isEnabled() ? (isMouseOver() ? textColour.brighter() : textColour) : disabledColour);
    g.drawFittedText(icon, getLocalBounds(), Justification::centred, 1, 1);
  }
  
private:
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  Colour textColour, disabledColour;
  fontaudio::IconName icon;
};

/*
 ==============================================================================
 Combo box displaying fontaudio icons
 ==============================================================================
 */

class IconComboBox : public ComboBox
{
public:
  IconComboBox()
  {
    setLookAndFeel(&lf);
  }
  
  ~IconComboBox()
  {
    setLookAndFeel(nullptr);
  }
  
private:
  FontaudioLookAndFeel lf;
};

/*
 ==============================================================================
 Container component for combo box based demo
 ==============================================================================
 */

class ComboBoxDemo : public Component
{
  
public:
  ComboBoxDemo(const String &title)
  {
    setOpaque(false);
    addAndMakeVisible(&combo);
    addAndMakeVisible(&label);
    label.setText(title, dontSendNotification);
  }
  
  void resized() override
  {
    Rectangle<float> bounds = getLocalBounds().toFloat();
    float labelWidth = bounds.getWidth() * 0.33f;
    float comboHeightReduce = bounds.getHeight() * 0.2f;
    
    //Rectangle<int> switchesRow = getLocalBounds().reduced(margin).removeFromTop(blockSize);
    label.setBounds(bounds.removeFromLeft(labelWidth).toNearestInt());
    combo.setBounds(bounds.reduced(0,comboHeightReduce).toNearestInt());
  }
  
  void addComboItem(fontaudio::IconName icon, int itemId)
  {
    combo.addItem(icon, itemId);
    combo.setSelectedId(1);
  }
  
private:
  Label label;
  IconComboBox combo;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComboBoxDemo)
};



class DigitalClockDemoPanel : public Component, public Timer
{
  
public:
  DigitalClockDemoPanel()
  {
    timeRefMilliseconds = 0;
    startTimer(timerInterval);
  };
  
  virtual ~DigitalClockDemoPanel(){};
  
  void paint(Graphics &g) override
  {
    g.setColour(Colours::lightcoral);
    g.setFont(sharedFontAudio->getFont(getHeight() * 0.8f));
    g.drawFittedText(currentTimecode, getLocalBounds(), Justification::centred, 1, 1);
  }
  
  void timerCallback() override
  {
    currentTimecode = String(msToTimecode(timeRefMilliseconds));
    repaint();
    timeRefMilliseconds += 25;
    
  }
  
  String msToTimecode(long long inputMilliseconds)
  {
    int milliseconds = (int)(inputMilliseconds % 1000);
    int seconds = (int)(inputMilliseconds / 1000) % 60;
    int minutes = (int)(inputMilliseconds / (1000 * 60)) % 60;
    int hours = (int)(inputMilliseconds / (1000 * 60 * 60)) % 24;
    
    std::ostringstream str;
    str << std::setw(2) << std::setfill('0') << hours;
    str << ":";
    str << std::setw(2) << std::setfill('0') << minutes;
    str << ":";
    str << std::setw(2) << std::setfill('0') << seconds;
    str << ".";
    str << std::setw(3) << std::setfill('0') << milliseconds;
    
    String normalStringTimecode = str.str();
    String fontaudioTimecode = "";
    
    for (auto ptr = normalStringTimecode.getCharPointer(); !ptr.isEmpty(); ++ptr)
    {
      auto c = *ptr;
      switch (c)
      {
        case '0':
          fontaudioTimecode += fontaudio::Digital0;
          break;
        case '1':
          fontaudioTimecode += fontaudio::Digital1;
          break;
        case '2':
          fontaudioTimecode += fontaudio::Digital2;
          break;
        case '3':
          fontaudioTimecode += fontaudio::Digital3;
          break;
        case '4':
          fontaudioTimecode += fontaudio::Digital4;
          break;
        case '5':
          fontaudioTimecode += fontaudio::Digital5;
          break;
        case '6':
          fontaudioTimecode += fontaudio::Digital6;
          break;
        case '7':
          fontaudioTimecode += fontaudio::Digital7;
          break;
        case '8':
          fontaudioTimecode += fontaudio::Digital8;
          break;
        case '9':
          fontaudioTimecode += fontaudio::Digital9;
          break;
        case '.':
          fontaudioTimecode += fontaudio::DigitalDot;
          break;
        case ':':
          fontaudioTimecode += fontaudio::DigitalColon;
          break;
      }
    }
    return fontaudioTimecode;
  }
  
  void stop(){
    if(isTimerRunning()){
      stopTimer();
    }
    
    currentTimecode = String(msToTimecode(timeRefMilliseconds=0));
    repaint();
  }
  
  void play(){
    if(!isTimerRunning())
      startTimer(timerInterval);
    
  }
  
  void pause(){
    if(isTimerRunning())
      stopTimer();
    else if(timeRefMilliseconds>0)
      play();
  };
  
private:
  int64 timeRefMilliseconds;
  int timerInterval = 25;
  int currentMilliseconds;
  String currentTimecode;
  SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DigitalClockDemoPanel)
};

/*
 ==============================================================================
 Rotary Slider using a Fontaudio Icon as UI
 ==============================================================================
 */
class RotarySlider : public Slider
{
public:
  RotarySlider(fontaudio::IconName icon, Colour sliderColour) : sliderColour(sliderColour),
  icon(icon)
  {
    setLookAndFeel(&lookAndFeel);
    setSliderStyle(SliderStyle::RotaryVerticalDrag);
    setColour(Slider::rotarySliderOutlineColourId, sliderColour);
    setTextBoxStyle(TextEntryBoxPosition::NoTextBox, true, 0, 0);
  };
  
  virtual ~RotarySlider()
  {
    setLookAndFeel(nullptr);
  };
  
  class RotarySliderLookAndFeel : public LookAndFeel_V4
  {
  private:
    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)
    {
      
      auto c = slider.findColour(Slider::rotarySliderOutlineColourId);
      fontaudio::IconName icon = dynamic_cast<RotarySlider *>(&slider)->getIcon();
      auto toAngle = rotaryEndAngle + sliderPos * (rotaryStartAngle - rotaryEndAngle);
      sharedFontAudio->drawCenterdRotated(g, icon, std::min(width, height), slider.isMouseOver() ? c.brighter() : c, slider.getLocalBounds(), toAngle / float_Pi, 1.0f);
    }
  };
  
  fontaudio::IconName getIcon() const
  {
    return icon;
  }
  
private:
  Colour sliderColour;
  fontaudio::IconName icon;
  RotarySliderLookAndFeel lookAndFeel;
  
};

/*
 ==============================================================================
 Linear Slider using a Fontaudio Icon as UI
 ==============================================================================
 */
class LinearSlider : public Slider
{
public:
  LinearSlider(fontaudio::IconName icon, Colour sliderColour) : sliderColour(sliderColour),
  icon(icon)
  {
    setLookAndFeel(&lookAndFeel);
    setSliderStyle(SliderStyle::LinearHorizontal);
    setColour(Slider::rotarySliderOutlineColourId, sliderColour);
    setTextBoxStyle(TextEntryBoxPosition::NoTextBox, true, 0, 0);
    setRange(0.0, 100.0);
  };
  
  virtual ~LinearSlider()
  {
    setLookAndFeel(nullptr);
  };
  
  class LinearSliderLookAndFeel : public LookAndFeel_V4
  {
  private:
    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;
  public:
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                          const float minSliderPos, const float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
    {
      auto c = slider.findColour(Slider::rotarySliderOutlineColourId);
      double sliderNormalizedValue = slider.valueToProportionOfLength(slider.getValue());
      bool isHorizontal = slider.isHorizontal();
      
      auto trackWidth = jmin(6.0f, isHorizontal ? height * 0.25f : width * 0.25f);
      
      Point<float> startPoint(isHorizontal ? x + height * 0.5f : x + width * 0.5f,
                              isHorizontal ? y + height * 0.5f : y + height -  width * 0.5f);
      
      
      Point<float> endPoint(isHorizontal ?  x + width - height*0.5f : startPoint.x,
                            isHorizontal ? startPoint.y : y + width * 0.5f);

      Point<float> valuePoint(isHorizontal ?  startPoint.x + sliderNormalizedValue*(endPoint.x-startPoint.x) : startPoint.x,
                              isHorizontal ? startPoint.y : startPoint.y + sliderNormalizedValue*(endPoint.y-startPoint.y) );

      
      Path backgroundTrack,valueTrack;
      backgroundTrack.startNewSubPath(startPoint);
      backgroundTrack.lineTo(endPoint);
      valueTrack.startNewSubPath(startPoint);
      valueTrack.lineTo(valuePoint);
      
      g.setColour(slider.findColour(Slider::backgroundColourId));
      g.strokePath(backgroundTrack, {trackWidth, PathStrokeType::curved, PathStrokeType::rounded});
      g.setColour(slider.findColour(Slider::trackColourId));
      g.strokePath(valueTrack, {trackWidth, PathStrokeType::curved, PathStrokeType::rounded});
      g.setColour(slider.findColour(Slider::thumbColourId));
     
      auto thumbWidth = isHorizontal ? height: width;
      
      fontaudio::IconName icon = dynamic_cast<LinearSlider *>(&slider)->getIcon();
      Rectangle<int> thumbRect = Rectangle<float>(static_cast<float>(thumbWidth), static_cast<float>(thumbWidth)).withCentre(valuePoint).toNearestInt();
      sharedFontAudio->drawCenterdRotated(g,
                                          icon,
                                          isHorizontal ? height : width,
                                          slider.isMouseOver() ? c.brighter() : c,
                                          thumbRect,
                                          isHorizontal ? -0.5f : 0.0f);
    }
  };
  
  fontaudio::IconName getIcon() const
  {
    return icon;
  }
  
private:
  Colour sliderColour;
  fontaudio::IconName icon;
  LinearSliderLookAndFeel lookAndFeel;
  
};
