/**
 * \file FrequencySelector.cpp
 */

#include "FrequencySelector.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    FrequencySelectorComponent::FrequencySelectorComponent (::juce::AudioProcessorValueTreeState& paramState, const std::string& name, const std::string& display, double min, double max, double default_)
    : frequencySlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), color(::juce::Colour(36, 36, 36))
    {
      addAndMakeVisible(frequencySlider);
      frequencyAtt.reset( new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, name, frequencySlider));
      frequencySlider.setRange (min, max);
      frequencySlider.setValue(default_);
      frequencySlider.setTextValueSuffix (" Hz");
      frequencySlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::orange);
      frequencySlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(frequencyLabel);
      frequencyLabel.setText(display, ::juce::NotificationType::dontSendNotification);
      frequencyLabel.setJustificationType(::juce::Justification::centred);
      
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (150, 150);
    }
    
    FrequencySelectorComponent::~FrequencySelectorComponent()
    {
    }
    
    void FrequencySelectorComponent::paint(::juce::Graphics& g)
    {
      g.setColour(color);
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }

    void FrequencySelectorComponent::resized()
    {
      frequencyLabel.setBoundsRelative(0.3, 0.05, 0.4, 0.1);
      frequencySlider.setBoundsRelative(0.1, 0.2, 0.8, 0.7);
    }
  }
}
