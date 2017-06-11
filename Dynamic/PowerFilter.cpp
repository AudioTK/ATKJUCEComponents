/**
 * \file PowerFilter.cpp
 */

#include "PowerFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    PowerFilterComponent::PowerFilterComponent (::juce::AudioProcessorValueTreeState& paramState, const std::string& powerName)
    : powerSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), color(::juce::Colour(16, 16, 16))
    {
      addAndMakeVisible(powerSlider);
      powerAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, powerName, powerSlider));
      powerSlider.setRange (0, 100);
      powerSlider.setSkewFactor(0.3);
      powerSlider.setTextValueSuffix (" ms");
      powerSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::rosybrown);
      powerSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(powerLabel);
      powerLabel.setText("RMS", ::juce::NotificationType::dontSendNotification);
      powerLabel.setJustificationType(::juce::Justification::centred);
    }
    
    PowerFilterComponent::~PowerFilterComponent()
    {
    }
    
    void PowerFilterComponent::paint(::juce::Graphics& g)
    {
      g.setColour(color);
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }

    void PowerFilterComponent::resized()
    {
      powerLabel.setBoundsRelative(0.1, 0.05, 0.8, 0.1);
      powerSlider.setBoundsRelative(0.1, 0.2, 0.8, 0.7);
    }
  }
}
