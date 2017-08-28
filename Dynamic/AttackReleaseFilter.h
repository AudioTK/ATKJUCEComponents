/**
 * \file AttackReleaseFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_ATTACKRELEASEFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_ATTACKRELEASEFILTER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
  namespace juce
  {
    class AttackReleaseFilterComponent  : public ::juce::Component
    {
    public:
      AttackReleaseFilterComponent(::juce::AudioProcessorValueTreeState& paramState, const std::string& attackName, const std::string& releaseName);
      ~AttackReleaseFilterComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void set_color(::juce::Colour color);
      
    private:
      ::juce::Slider attackSlider;
      ::juce::Slider releaseSlider;
      ::juce::Label attackLabel;
      ::juce::Label releaseLabel;
      ::juce::Colour color;
      
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> attackAtt;
      std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment> releaseAtt;
    };
  }
}

#endif
