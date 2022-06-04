/**
 * \file SyncUniversalFixedDelayFilter.cpp
 */

#include "SyncUniversalFixedDelayFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
namespace juce
{
SyncUniversalFixedDelayFilterComponent::SyncUniversalFixedDelayFilterComponent(
    ::juce::AudioProcessorValueTreeState& paramState,
    const std::string& delayName, const std::string& blendName,
    const std::string& feedbackName, const std::string& feedforwardName)
    : delaySlider(::juce::Slider::SliderStyle::Rotary,
                  ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      blendSlider(::juce::Slider::SliderStyle::Rotary,
                  ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      feedbackSlider(::juce::Slider::SliderStyle::Rotary,
                     ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      feedforwardSlider(::juce::Slider::SliderStyle::Rotary,
                        ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      color(::juce::Colour(10, 10, 10))
{
    addAndMakeVisible(delaySlider);
    delayAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, delayName, delaySlider));
    delaySlider.setTextValueSuffix(" ms");
    delaySlider.setColour(::juce::Slider::rotarySliderFillColourId,
                          ::juce::Colours::aliceblue);
    delaySlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(delayLabel);
    delayLabel.setText("Delay", ::juce::NotificationType::dontSendNotification);
    delayLabel.setJustificationType(::juce::Justification::centred);

    addAndMakeVisible(blendSlider);
    blendAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, blendName, blendSlider));
    blendSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                          ::juce::Colours::cadetblue);
    blendSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(blendLabel);
    blendLabel.setText("Blend", ::juce::NotificationType::dontSendNotification);
    blendLabel.setJustificationType(::juce::Justification::centred);

    addAndMakeVisible(feedbackSlider);
    feedbackAtt.reset(
        new ::juce::AudioProcessorValueTreeState::SliderAttachment(
            paramState, feedbackName, feedbackSlider));
    feedbackSlider.setTextValueSuffix("");
    feedbackSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                             ::juce::Colours::cornflowerblue);
    feedbackSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("Feedback",
                          ::juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(::juce::Justification::centred);

    addAndMakeVisible(feedforwardSlider);
    feedforwardAtt.reset(
        new ::juce::AudioProcessorValueTreeState::SliderAttachment(
            paramState, feedforwardName, feedforwardSlider));
    feedforwardSlider.setTextValueSuffix("");
    feedforwardSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                                ::juce::Colours::deepskyblue);
    feedforwardSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());

    addAndMakeVisible(feedforwardLabel);
    feedforwardLabel.setText("Feedforward",
                             ::juce::NotificationType::dontSendNotification);
    feedforwardLabel.setJustificationType(::juce::Justification::centred);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(450, 150);
}

SyncUniversalFixedDelayFilterComponent::~SyncUniversalFixedDelayFilterComponent() = default;

void SyncUniversalFixedDelayFilterComponent::paint(::juce::Graphics& g)
{
    g.setColour(color);
    g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
}

void SyncUniversalFixedDelayFilterComponent::resized()
{
    delayLabel.setBoundsRelative(0.1 / 4, 0.05, 0.8 / 4, 0.1);
    delaySlider.setBoundsRelative(0.1 / 4, 0.2, 0.8 / 4, 0.7);
    blendLabel.setBoundsRelative(1.1 / 4, 0.05, 0.8 / 4, 0.1);
    blendSlider.setBoundsRelative(1.1 / 4, 0.2, 0.8 / 4, 0.7);
    feedbackLabel.setBoundsRelative(2.1 / 4, 0.05, 0.8 / 4, 0.1);
    feedbackSlider.setBoundsRelative(2.1 / 4, 0.2, 0.8 / 4, 0.7);
    feedforwardLabel.setBoundsRelative(3.1 / 4, 0.05, 0.8 / 4, 0.1);
    feedforwardSlider.setBoundsRelative(3.1 / 4, 0.2, 0.8 / 4, 0.7);
}
} // namespace juce
} // namespace ATK
