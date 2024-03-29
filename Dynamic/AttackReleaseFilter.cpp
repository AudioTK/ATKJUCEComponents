/**
 * \file AttackReleaseFilter.cpp
 */

#include "AttackReleaseFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
namespace juce
{
AttackReleaseFilterComponent::AttackReleaseFilterComponent(
    ::juce::AudioProcessorValueTreeState& paramState,
    const std::string& attackName, const std::string& releaseName)
    : attackSlider(::juce::Slider::SliderStyle::Rotary,
                   ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      releaseSlider(::juce::Slider::SliderStyle::Rotary,
                    ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      color(::juce::Colour(56, 56, 56))
{
    addAndMakeVisible(attackSlider);
    attackAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, attackName, attackSlider));
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                           ::juce::Colours::rosybrown);
    attackSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack",
                        ::juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(::juce::Justification::centred);

    addAndMakeVisible(releaseSlider);
    releaseAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, releaseName, releaseSlider));
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                            ::juce::Colours::skyblue);
    releaseSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release",
                         ::juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(::juce::Justification::centred);
}

AttackReleaseFilterComponent::~AttackReleaseFilterComponent() {}

void AttackReleaseFilterComponent::paint(::juce::Graphics& g)
{
    g.setColour(color);
    g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
}

void AttackReleaseFilterComponent::resized()
{
    attackLabel.setBoundsRelative(0, 0.05, 0.5, 0.1);
    attackSlider.setBoundsRelative(0.05, 0.2, 0.4, 0.7);
    releaseLabel.setBoundsRelative(0.5, 0.05, 0.5, 0.1);
    releaseSlider.setBoundsRelative(0.55, 0.2, 0.4, 0.7);
}
} // namespace juce
} // namespace ATK
