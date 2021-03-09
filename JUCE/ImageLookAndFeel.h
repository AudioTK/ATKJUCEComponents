/**
 * \file ImageLookAndFeel.h
 */

#ifndef ATKJUCECOMPONENTS_JUCE_IMAGELOOKANDFEEL
#define ATKJUCECOMPONENTS_JUCE_IMAGELOOKANDFEEL

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

namespace ATK
{
namespace juce
{
/// Draws a rotary slider, starting from the left to the right
class ImageLookAndFeel: public ::juce::LookAndFeel_V2
{
  ::juce::Image image;
  int width;
  int height;
  int nb;
public:
  ImageLookAndFeel(::juce::Image image, int width, int height, int nb);

  void drawRotarySlider(::juce::Graphics& g,
      int x,
      int y,
      int width,
      int height,
      float sliderPos,
      const float rotaryStartAngle,
      const float rotaryEndAngle,
      ::juce::Slider& slider) override final;
  
  int getWidth() const { return width; }
  int getHeight() const { return height; }
};
} // namespace juce
} // namespace ATK

#endif
