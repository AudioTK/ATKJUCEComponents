/**
 * \file GainCompressorFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DYNAMIC_GAINCOMPRESSORFILTER
#define ATKJUCECOMPONENTS_DYNAMIC_GAINCOMPRESSORFILTER

#include <AppConfig.h>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <ATK/Dynamic/AttackReleaseFilter.h>

namespace ATK
{
namespace juce
{
class GainCompressorFilterComponent : public ::juce::Component
{
  public:
    GainCompressorFilterComponent(
        ::juce::AudioProcessorValueTreeState& paramState,
        const std::string& thresholdName, double thresholdMin,
        double thresholdMax, const std::string& ratioName, double ratioMin,
        double ratioMax, const std::string& softnessName);
    ~GainCompressorFilterComponent();

    //==============================================================================
    void paint(::juce::Graphics&) override;
    void resized() override;
    void set_color(::juce::Colour color);

  private:
    ::juce::Slider thresholdSlider;
    ::juce::Slider ratioSlider;
    ::juce::Slider softnessSlider;
    ::juce::Label thresholdLabel;
    ::juce::Label ratioLabel;
    ::juce::Label softnessLabel;
    ::juce::Colour color;

    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        thresholdAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        ratioAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        softnessAtt;
};
} // namespace juce
} // namespace ATK

#endif
