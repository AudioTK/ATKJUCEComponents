/**
 * \file ToneStackFilter.cpp
 */

#include "ToneStackFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
namespace juce
{
ToneStackFilterComponent::ToneStackFilterComponent(
    ::juce::AudioProcessorValueTreeState& paramState, const std::string& bass,
    const std::string& medium, const std::string& high)
    : lowSlider(::juce::Slider::SliderStyle::Rotary,
                ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      mediumSlider(::juce::Slider::SliderStyle::Rotary,
                   ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      highSlider(::juce::Slider::SliderStyle::Rotary,
                 ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      color(::juce::Colour(46, 46, 46))
{
    addAndMakeVisible(lowSlider);
    bassAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, bass, lowSlider));
    lowSlider.setRange(-1, 1);
    lowSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                        ::juce::Colours::mediumpurple);
    lowSlider.setLookAndFeel(&DualSliderLookAndFeel::get_instance());
    addAndMakeVisible(mediumSlider);
    mediumAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, medium, mediumSlider));
    mediumSlider.setRange(-1, 1);
    mediumSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                           ::juce::Colours::darkviolet);
    mediumSlider.setLookAndFeel(&DualSliderLookAndFeel::get_instance());
    addAndMakeVisible(highSlider);
    highAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment(
        paramState, high, highSlider));
    highSlider.setRange(-1, 1);
    highSlider.setColour(::juce::Slider::rotarySliderFillColourId,
                         ::juce::Colours::purple);
    highSlider.setLookAndFeel(&DualSliderLookAndFeel::get_instance());

    addAndMakeVisible(lowLabel);
    lowLabel.setText("Low", ::juce::NotificationType::dontSendNotification);
    lowLabel.setJustificationType(::juce::Justification::centred);
    addAndMakeVisible(mediumLabel);
    mediumLabel.setText("Middle",
                        ::juce::NotificationType::dontSendNotification);
    mediumLabel.setJustificationType(::juce::Justification::centred);
    addAndMakeVisible(highLabel);
    highLabel.setText("High", ::juce::NotificationType::dontSendNotification);
    highLabel.setJustificationType(::juce::Justification::centred);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(450, 150);
}

ToneStackFilterComponent::~ToneStackFilterComponent() {}

void ToneStackFilterComponent::paint(::juce::Graphics& g)
{
    g.setColour(color);
    g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
}

void ToneStackFilterComponent::resized()
{
    lowLabel.setBoundsRelative(0, .05, 1. / 3, .1);
    lowSlider.setBoundsRelative(.1 / 3, .2, 4. / 15, .7);
    mediumLabel.setBoundsRelative(1. / 3, .05, 1. / 3, .1);
    mediumSlider.setBoundsRelative(1.1 / 3, .2, 4. / 15, .7);
    highLabel.setBoundsRelative(2. / 3, .05, 1. / 3, .1);
    highSlider.setBoundsRelative(2.1 / 3, .2, 4. / 15, .7);
}
} // namespace juce
} // namespace ATK
