/**
 * \file ToneStackFilter.cpp
 */

#include "ToneStackFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    ToneStackFilterComponent::ToneStackFilterComponent (ATK::IIRFilter<ATK::ToneStackCoefficients<double> >& filter)
    : filter (filter),
      lowSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      mediumSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      highSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow),
      color(::juce::Colour(26, 26, 26))
    {
      addAndMakeVisible(lowSlider);
      lowSlider.setRange (0, 1);
      lowSlider.setValue(0.5);
      lowSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::orange);
      lowSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      addAndMakeVisible(mediumSlider);
      mediumSlider.setRange (0, 1);
      mediumSlider.setValue(0.5);
      mediumSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::orange);
      mediumSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      addAndMakeVisible(highSlider);
      highSlider.setRange (0, 1);
      highSlider.setValue(0.5);
      highSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::orange);
      highSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(lowLabel);
      lowLabel.setText("low", ::juce::NotificationType::dontSendNotification);
      lowLabel.setJustificationType(::juce::Justification::centred);
      addAndMakeVisible(mediumLabel);
      mediumLabel.setText("low", ::juce::NotificationType::dontSendNotification);
      mediumLabel.setJustificationType(::juce::Justification::centred);
      addAndMakeVisible(highLabel);
      highLabel.setText("low", ::juce::NotificationType::dontSendNotification);
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
      mediumLabel.setBounds(200, 10, 400, 20);
      mediumSlider.setBounds(220, 40, 360, 140);
      highLabel.setBounds(400, 10, 600, 20);
      highSlider.setBounds(420, 40, 560, 140);
    }
    
    void ToneStackFilterComponent::sliderValueChanged(::juce::Slider* slider)
    {
      if(slider == &lowSlider)
      {
        filter.set_low(slider->getValue());
      }
      else if(slider == &mediumSlider)
      {
        filter.set_middle(slider->getValue());
      }
      else if(slider == &highSlider)
      {
        filter.set_high(slider->getValue());
      }
    }
  }
}
