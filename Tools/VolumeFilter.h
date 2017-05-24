/**
 * \file VolumeFilter.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_VOLUMEFILTER
#define ATKJUCECOMPONENTS_TOOLS_VOLUMEFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Tools/VolumeFilter.h>

namespace ATK
{
  namespace juce
  {
    class VolumeFilterComponent  : public ::juce::Component
    {
    public:
      VolumeFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& name, const std::string& display, double min, double max);
      ~VolumeFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider levelSlider;
      ::juce::Label levelLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> volumeAtt;
      
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeFilterComponent)
    };    
  }
}

#endif
