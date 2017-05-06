/**
 * \file DryWetFilter.cpp
 */

#include "DryWetFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    DryWetFilterComponent::DryWetFilterComponent (::juce::AudioParameterFloat* drywet)
    : drywet(drywet), levelSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), color(::juce::Colour(46, 46, 46))
    {
      addAndMakeVisible(levelSlider);
      levelSlider.setRange (0, 100);
      levelSlider.setValue(100);
      levelSlider.setTextValueSuffix (" %");
      levelSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::aqua);
      levelSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      levelSlider.addListener (this);
      
      addAndMakeVisible(levelLabel);
      levelLabel.setText("Dry/Wet", ::juce::NotificationType::dontSendNotification);
      levelLabel.setJustificationType(::juce::Justification::centred);
      
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (150, 150);
    }
    
    DryWetFilterComponent::~DryWetFilterComponent()
    {
    }
    
    void DryWetFilterComponent::paint(::juce::Graphics& g)
    {
      g.setColour(color);
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }

    void DryWetFilterComponent::resized()
    {
      levelLabel.setBoundsRelative(0.3, 0.05, 0.4, 0.1);
      levelSlider.setBoundsRelative(0.1, 0.2, 0.8, 0.7);
    }
    
    void DryWetFilterComponent::sliderValueChanged(::juce::Slider* slider)
    {
      if(slider == &levelSlider)
      {
        *drywet = slider->getValue();
      }
    }
  }
}
