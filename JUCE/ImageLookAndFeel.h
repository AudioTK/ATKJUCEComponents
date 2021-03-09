/**
 * \file ImageLookAndFeel.h
 */

#ifndef ATKJUCECOMPONENTS_JUCE_IMAGELOOKANDFEEL
#define ATKJUCECOMPONENTS_JUCE_IMAGELOOKANDFEEL

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>

namespace ATK
{
namespace juce
{
/// Draws a rotary slider, starting from the left to the right
class ImageLookAndFeel: public ::juce::LookAndFeel_V2
{
public:
  static ImageLookAndFeel& get_instance();

  void drawRotarySlider(::juce::Graphics& g,
      int x,
      int y,
      int width,
      int height,
      float sliderPos,
      const float rotaryStartAngle,
      const float rotaryEndAngle,
      ::juce::Slider& slider) override final;
};
} // namespace juce
} // namespace ATK

#endif
