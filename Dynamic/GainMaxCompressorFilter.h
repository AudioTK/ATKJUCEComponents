/**
 * \file GainMaxCompressorFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_GAINMAXCOMPRESSORFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_GAINMAXCOMPRESSORFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
  namespace juce
  {
    class GainMaxCompressorFilterComponent  : public ::juce::Component
    {
    public:
      GainMaxCompressorFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& thresholdName, const std::string& ratioName, const std::string& softnessName, const std::string& reducName);
      ~GainMaxCompressorFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider thresholdSlider;
      ::juce::Slider ratioSlider;
      ::juce::Slider softnessSlider;
      ::juce::Slider reducSlider;
      ::juce::Label thresholdLabel;
      ::juce::Label ratioLabel;
      ::juce::Label softnessLabel;
      ::juce::Label reducLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> ratioAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> softnessAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> reducAtt;
    };
  }
}

#endif
