/**
 * \file LookAndFeel.h
 */

#ifndef ATKJUCECOMPONENTS_JUCE_LOOKANDFEEL
#define ATKJUCECOMPONENTS_JUCE_LOOKANDFEEL

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>

namespace ATK
{
  namespace juce
  {
    class SimpleSliderLookAndFeel: public ::juce::LookAndFeel_V2
    {
    public:
      static SimpleSliderLookAndFeel& get_instance();
      
      void drawRotarySlider (::juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                             const float rotaryStartAngle, const float rotaryEndAngle, ::juce::Slider& slider) override final;
    };
  }
}

#endif
