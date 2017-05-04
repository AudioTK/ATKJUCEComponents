/**
 * \file DryWetFilter.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_DRYWETFILTER
#define ATKJUCECOMPONENTS_TOOLS_DRYWETFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Tools/DryWetFilter.h>

namespace ATK
{
  namespace juce
  {
    class DryWetFilterComponent  : public ::juce::Component, public ::juce::Slider::Listener
    {
    public:
      DryWetFilterComponent(::juce::AudioParameterFloat* drywet);
      ~DryWetFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
    
    protected:
      void sliderValueChanged (::juce::Slider* slider) override final;
      
    private:
      // This reference is provided as a quick way for your editor to
      // access the processor object that created it.
      ::juce::AudioParameterFloat* drywet;
      
      ::juce::Slider levelSlider;
      ::juce::Label levelLabel;
      ::juce::Colour color;
      
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DryWetFilterComponent)
    };    
  }
}

#endif
