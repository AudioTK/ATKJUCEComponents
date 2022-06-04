/**
 * \file Slider.cpp
 */

#include "Slider.h"

#include "ImageLookAndFeel.h"

namespace ATK
{
namespace juce
{
SliderComponent::SliderComponent(
    ::juce::AudioProcessorValueTreeState& paramState, const std::string& name,
    const std::string& display, ImageLookAndFeel* laf)
    : levelSlider(::juce::Slider::SliderStyle::Rotary,
                  ::juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    addAndMakeVisible(levelSlider);
    sliderAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, name, levelSlider));
    levelSlider.setLookAndFeel(laf);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(laf->getHeight(), laf->getWidth());
}

SliderComponent::~SliderComponent() = default;

void SliderComponent::paint(::juce::Graphics& g) {}

void SliderComponent::resized() { levelSlider.setBoundsRelative(0, 0, 1, 1); }
} // namespace juce
} // namespace ATK
