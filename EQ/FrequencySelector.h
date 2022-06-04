/**
 * \file FrequencySelector.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_FREQUENCYSELECTOR
#define ATKJUCECOMPONENTS_TOOLS_FREQUENCYSELECTOR

#include <AppConfig.h>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <ATK/Tools/VolumeFilter.h>

namespace ATK
{
namespace juce
{
class FrequencySelectorComponent : public ::juce::Component
{
  public:
    FrequencySelectorComponent(::juce::AudioProcessorValueTreeState& paramState,
                               const std::string& name,
                               const std::string& display);
    ~FrequencySelectorComponent();

    //==============================================================================
    void paint(::juce::Graphics&) override;
    void resized() override;
    void set_color(::juce::Colour color);

  private:
    ::juce::Slider frequencySlider;
    ::juce::Label frequencyLabel;
    ::juce::Colour color;

    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        frequencyAtt;
};
} // namespace juce
} // namespace ATK

#endif
