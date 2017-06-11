/**
 * \file PowerFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_POWERFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_POWERFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
  namespace juce
  {
    class PowerFilterComponent  : public ::juce::Component
    {
    public:
      PowerFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& powerName, double powerMin, double powerMax);
      ~PowerFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider powerSlider;
      ::juce::Label powerLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> powerAtt;

      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PowerFilterComponent)
    };
  }
}

#endif