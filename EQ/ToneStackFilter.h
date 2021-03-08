/**
 * \file ToneStackFilter.h
 */

#ifndef ATKJUCECOMPONENTS_EQ_TONESTACKFILTER
#define ATKJUCECOMPONENTS_EQ_TONESTACKFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

namespace ATK
{
  namespace juce
  {
    class ToneStackFilterComponent  : public ::juce::Component
    {
    public:
      ToneStackFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& bass, const std::string& medium, const std::string& high);
      ~ToneStackFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      // This reference is provided as a quick way for your editor to
      // access the processor object that created it.
      ::juce::Slider lowSlider;
      ::juce::Label lowLabel;
      ::juce::Slider mediumSlider;
      ::juce::Label mediumLabel;
      ::juce::Slider highSlider;
      ::juce::Label highLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> bassAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> mediumAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> highAtt;
    };

  }
}

#endif
