/**
 * \file GainSwellFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_GAINSWELLFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_GAINSWELLFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
  namespace juce
  {
    class GainSwellFilterComponent  : public ::juce::Component
    {
    public:
      GainSwellFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& thresholdName, const std::string& ratioName, const std::string& softnessName);
      ~GainSwellFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider thresholdSlider;
      ::juce::Slider ratioSlider;
      ::juce::Slider softnessSlider;
      ::juce::Label thresholdLabel;
      ::juce::Label ratioLabel;
      ::juce::Label softnessLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> ratioAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> softnessAtt;
    };
  }
}

#endif
