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
    class VolumeFilterComponent  : public ::juce::Component, public ::juce::Slider::Listener
    {
    public:
      VolumeFilterComponent(VolumeFilter<double>& filter, ::juce::String display, double min, double max, double default_);
      ~VolumeFilterComponent();
      
      //==============================================================================
      void resized() override;
    
    protected:
      void sliderValueChanged (::juce::Slider* slider) override final;
      
    private:
      // This reference is provided as a quick way for your editor to
      // access the processor object that created it.
      VolumeFilter<double>& filter;
      
      ::juce::Slider levelSlider;
      ::juce::Label levelLabel;
      
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeFilterComponent)
    };
    
  }
}

#endif
