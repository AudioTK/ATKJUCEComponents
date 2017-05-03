/**
 * \file VolumeFilter.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_VOLUMEFILTER
#define ATKJUCECOMPONENTS_TOOLS_VOLUMEFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>

#include <ATK/Tools/VolumeFilter.h>

namespace ATK
{
  namespace juce
  {
    class VolumeFilterComponent  : public ::juce::Component
    {
    public:
      VolumeFilterComponent(VolumeFilter<double>& filter, ::juce::String display, double min, double max, double default_);
      ~VolumeFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;

      void set_color(::juce::Colour color);
      
    private:
      // This reference is provided as a quick way for your editor to
      // access the processor object that created it.
      VolumeFilter<double>& filter;
      
      ::juce::Slider levelSlider;
      ::juce::Label levelLabel;
      ::juce::Colour color;
      
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeFilterComponent)
    };
    
  }
}

#endif
