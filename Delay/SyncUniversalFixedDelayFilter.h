/**
 * \file SyncUniversalFixedDelayFilter.h
 */

#ifndef ATKJUCECOMPONENTS_DELAY_SYNCUNIVERSALFIXEDDELAYFILTER
#define ATKJUCECOMPONENTS_DELAY_SYNCUNIVERSALFIXEDDELAYFILTER

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace ATK
{
namespace juce
{
class SyncUniversalFixedDelayFilterComponent : public ::juce::Component
{
  public:
    SyncUniversalFixedDelayFilterComponent(
        ::juce::AudioProcessorValueTreeState& paramState,
        const std::string& delayNumName, const std::string& delayDenomName,
        const std::string& blendName, const std::string& feedbackName,
        const std::string& feedforwardName);
    ~SyncUniversalFixedDelayFilterComponent();

    //==============================================================================
    void paint(::juce::Graphics&) override;
    void resized() override;
    void set_color(::juce::Colour color);

  private:
    ::juce::Slider delayNumSlider;
    ::juce::Slider delayDenomSlider;
    ::juce::Slider blendSlider;
    ::juce::Slider feedbackSlider;
    ::juce::Slider feedforwardSlider;
    ::juce::Label delayNumLabel;
    ::juce::Label delayDenomLabel;
    ::juce::Label blendLabel;
    ::juce::Label feedbackLabel;
    ::juce::Label feedforwardLabel;
    ::juce::Colour color;

    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        delayNumAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        delayDenomAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        blendAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        feedbackAtt;
    std::unique_ptr<::juce::AudioProcessorValueTreeState::SliderAttachment>
        feedforwardAtt;
};
} // namespace juce
} // namespace ATK

#endif
