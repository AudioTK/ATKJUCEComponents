/**
 * \file GainMAxColoredExpanderFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER

#include <AppConfig.h>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
namespace juce
{
class GainMaxColoredExpanderFilterComponent : public ::juce::Component
{
  public:
    GainMaxColoredExpanderFilterComponent(
        ::juce::AudioProcessorValueTreeState& paramState,
        const std::string& thresholdName, const std::string& ratioName,
        const std::string& softnessName, const std::string& colorName,
        const std::string& qualityName, const std::string& reducName);
    ~GainMaxColoredExpanderFilterComponent();

    //==============================================================================
    void paint(::juce::Graphics&) override;
    void resized() override;
    void set_color(::juce::Colour color);

  private:
    ::juce::Slider thresholdSlider;
    ::juce::Slider ratioSlider;
    ::juce::Slider softnessSlider;
    ::juce::Slider colorSlider;
    ::juce::Slider qualitySlider;
    ::juce::Slider reducSlider;
    ::juce::Label thresholdLabel;
    ::juce::Label ratioLabel;
    ::juce::Label softnessLabel;
    ::juce::Label colorLabel;
    ::juce::Label qualityLabel;
    ::juce::Label reducLabel;
    ::juce::Colour color;

    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        thresholdAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        ratioAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        softnessAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        colorAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        qualityAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        reducAtt;
};
} // namespace juce
} // namespace ATK

#endif
