/**
 * \file ToneStackFilter.h
 */

#ifndef ATKJUCECOMPONENTS_EQ_TONESTACKFILTER
#define ATKJUCECOMPONENTS_EQ_TONESTACKFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>

#include <ATK/EQ/IIRFilter.h>
#include <ATK/EQ/ToneStackFilter.h>

namespace ATK
{
  namespace juce
  {
    class ToneStackFilterComponent  : public ::juce::Component, public ::juce::Slider::Listener
    {
    public:
      ToneStackFilterComponent(ATK::IIRFilter<ATK::ToneStackCoefficients<double> >& filter);
      ~ToneStackFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    protected:
      void sliderValueChanged (::juce::Slider* slider) override final;
      
    private:
      // This reference is provided as a quick way for your editor to
      // access the processor object that created it.
      ATK::IIRFilter<ATK::ToneStackCoefficients<double> >& filter;
      
      ::juce::Slider lowSlider;
      ::juce::Label lowLabel;
      ::juce::Slider mediumSlider;
      ::juce::Label mediumLabel;
      ::juce::Slider highSlider;
      ::juce::Label highLabel;
      ::juce::Colour color;
      
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneStackFilterComponent)
    };

  }
}

#endif
