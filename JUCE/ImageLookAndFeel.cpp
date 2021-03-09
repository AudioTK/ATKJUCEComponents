/**
 * \file ImageLookAndFeel.cpp
 */

#include "ImageLookAndFeel.h"

namespace ATK
{
namespace juce
{
ImageLookAndFeel::ImageLookAndFeel(::juce::Image image, int width, int height, int nb)
: image(std::move(image))
, width(width)
, height(height)
, nb(nb)
{
}

void ImageLookAndFeel::drawRotarySlider(::juce::Graphics& g,
    int x,
    int y,
    int width,
    int height,
    float sliderPos,
    const float rotaryStartAngle,
    const float rotaryEndAngle,
    ::juce::Slider& slider)
{
  g.drawImage(image, x, y, width, height, 0, std::lround((nb - 1) * sliderPos) * getHeight(), getWidth(), getHeight());
}
} // namespace juce
} // namespace ATK
