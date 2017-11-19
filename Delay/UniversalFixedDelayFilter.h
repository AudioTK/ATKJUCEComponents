/**
 * \file UniversalFixedDelayFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DELAY_UNIVERSALFIXEDDELAYFILTER
#define ATKJUCECOMPONENTS_DELAY_UNIVERSALFIXEDDELAYFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace ATK
{
  namespace juce
  {
    class UniversalFixedDelayFilterComponent  : public ::juce::Component
    {
    public:
      UniversalFixedDelayFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& delayName, const std::string& blendName, const std::string& feedbackName, const std::string& feedforwardName);
      ~UniversalFixedDelayFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider delaySlider;
      ::juce::Slider blendSlider;
      ::juce::Slider feedbackSlider;
      ::juce::Slider feedforwardSlider;
      ::juce::Label delayLabel;
      ::juce::Label blendLabel;
      ::juce::Label feedbackLabel;
      ::juce::Label feedforwardLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> delayAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> blendAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> feedforwardAtt;
    };
  }
}

#endif
