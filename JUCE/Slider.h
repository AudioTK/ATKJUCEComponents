/**
 * \file VolumeFilter.h
 */

#ifndef ATKJUCECOMPONENTS_JUCE_SLIDER
#define ATKJUCECOMPONENTS_JUCE_SLIDER

#include <AppConfig.h>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "ImageLookAndFeel.h"

namespace ATK
{
namespace juce
{
class SliderComponent: public ::juce::Component
{
public:
  SliderComponent(::juce::AudioProcessorValueTreeState& paramState,
      const std::string& name,
      const std::string& display,
      ImageLookAndFeel* laf);
  ~SliderComponent();

  //==============================================================================
  void paint(::juce::Graphics&) override;
  void resized() override;
  void set_color(::juce::Colour color);

private:
  ::juce::Slider levelSlider;

  std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> sliderAtt;
};
} // namespace juce
} // namespace ATK

#endif
