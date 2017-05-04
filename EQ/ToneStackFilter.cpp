/**
 * \file ToneStackFilter.cpp
 */

#include "ToneStackFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    ToneStackFilterComponent::ToneStackFilterComponent(::juce::AudioParameterFloat* bass, ::juce::AudioParameterFloat* medium, ::juce::AudioParameterFloat* high)
    : bass(bass), medium(medium), high(high),
      lowSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      mediumSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      highSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      color(::juce::Colour(46, 46, 46))
    {
      addAndMakeVisible(lowSlider);
      lowSlider.setRange (0, 1);
      lowSlider.setValue(0.5);
      lowSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::mediumpurple);
      lowSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      highSlider.addListener (this);
      addAndMakeVisible(mediumSlider);
      mediumSlider.setRange (0, 1);
      mediumSlider.setValue(0.5);
      mediumSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::darkviolet);
      mediumSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      highSlider.addListener (this);
      addAndMakeVisible(highSlider);
      highSlider.setRange (0, 1);
      highSlider.setValue(0.5);
      highSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::purple);
      highSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      highSlider.addListener (this);
      
      addAndMakeVisible(lowLabel);
      lowLabel.setText("low", ::juce::NotificationType::dontSendNotification);
      lowLabel.setJustificationType(::juce::Justification::centred);
      addAndMakeVisible(mediumLabel);
      mediumLabel.setText("middle", ::juce::NotificationType::dontSendNotification);
      mediumLabel.setJustificationType(::juce::Justification::centred);
      addAndMakeVisible(highLabel);
      highLabel.setText("high", ::juce::NotificationType::dontSendNotification);
      highLabel.setJustificationType(::juce::Justification::centred);
    
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (600, 200);
    }
    
    ToneStackFilterComponent::~ToneStackFilterComponent()
    {
    }
    
    void ToneStackFilterComponent::paint(::juce::Graphics& g)
    {
      g.setColour(color);
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }
    
    void ToneStackFilterComponent::resized()
    {
      lowLabel.setBounds(0, 10, 200, 20);
      lowSlider.setBounds(20, 40, 160, 140);
      mediumLabel.setBounds(200, 10, 200, 20);
      mediumSlider.setBounds(220, 40, 160, 140);
      highLabel.setBounds(400, 10, 200, 20);
      highSlider.setBounds(420, 40, 160, 140);
    }
    
    void ToneStackFilterComponent::sliderValueChanged(::juce::Slider* slider)
    {
      if(slider == &lowSlider)
      {
        *bass = slider->getValue();
      }
      else if(slider == &mediumSlider)
      {
        *medium = slider->getValue();
      }
      else if(slider == &highSlider)
      {
        *high = slider->getValue();
      }
    }
  }
}
