/**
 * \file GainMaxColoredExpanderFilter.cpp
 */

#include "GainMaxColoredExpanderFilter.h"

#include "../JUCE/LookAndFeel.h"

namespace ATK
{
  namespace juce
  {
    GainMaxColoredExpanderFilterComponent::GainMaxColoredExpanderFilterComponent (::juce::AudioProcessorValueTreeState& paramState, const std::string& thresholdName, const std::string& ratioName, const std::string& softnessName, const std::string& colorName, const std::string& qualityName, const std::string& reducName)
    : thresholdSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), ratioSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), softnessSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), colorSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), qualitySlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), reducSlider(::juce::Slider::SliderStyle::Rotary, ::juce::Slider::TextEntryBoxPosition::TextBoxBelow), color(::juce::Colour(16, 16, 16))
    {
      addAndMakeVisible(thresholdSlider);
      thresholdAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, thresholdName, thresholdSlider));
      thresholdSlider.setTextValueSuffix (" dB");
      thresholdSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::palegoldenrod);
      thresholdSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(thresholdLabel);
      thresholdLabel.setText("Threshold", ::juce::NotificationType::dontSendNotification);
      thresholdLabel.setJustificationType(::juce::Justification::centred);

      addAndMakeVisible(ratioSlider);
      ratioAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, ratioName, ratioSlider));
      ratioSlider.setTextValueSuffix ("/1");
      ratioSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::goldenrod);
      ratioSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(ratioLabel);
      ratioLabel.setText("Ratio", ::juce::NotificationType::dontSendNotification);
      ratioLabel.setJustificationType(::juce::Justification::centred);

      addAndMakeVisible(softnessSlider);
      softnessAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, softnessName, softnessSlider));
      softnessSlider.setTextValueSuffix ("");
      softnessSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::darkgoldenrod);
      softnessSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(softnessLabel);
      softnessLabel.setText("Softness", ::juce::NotificationType::dontSendNotification);
      softnessLabel.setJustificationType(::juce::Justification::centred);
      
      addAndMakeVisible(colorSlider);
      colorAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, colorName, colorSlider));
      colorSlider.setTextValueSuffix ("");
      colorSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::gold);
      colorSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(colorLabel);
      colorLabel.setText("Color", ::juce::NotificationType::dontSendNotification);
      colorLabel.setJustificationType(::juce::Justification::centred);
      
      addAndMakeVisible(qualitySlider);
      qualityAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, qualityName, qualitySlider));
      qualitySlider.setTextValueSuffix ("");
      qualitySlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::gold);
      qualitySlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(qualityLabel);
      qualityLabel.setText("Quality", ::juce::NotificationType::dontSendNotification);
      qualityLabel.setJustificationType(::juce::Justification::centred);
      
      addAndMakeVisible(reducSlider);
      reducAtt.reset(new ::juce::AudioProcessorValueTreeState::SliderAttachment (paramState, reducName, reducSlider));
      reducSlider.setTextValueSuffix(" dB");
      reducSlider.setColour(::juce::Slider::rotarySliderFillColourId, ::juce::Colours::gold);
      reducSlider.setLookAndFeel(&SimpleSliderLookAndFeel::get_instance());
      
      addAndMakeVisible(reducLabel);
      reducLabel.setText("Max reduction", ::juce::NotificationType::dontSendNotification);
      reducLabel.setJustificationType(::juce::Justification::centred);
    }
    
    GainMaxColoredExpanderFilterComponent::~GainMaxColoredExpanderFilterComponent()
    {
    }
    
    void GainMaxColoredExpanderFilterComponent::paint(::juce::Graphics& g)
    {
      g.setColour(color);
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }

    void GainMaxColoredExpanderFilterComponent::resized()
    {
      const int nb_elements = 6;
      thresholdLabel.setBoundsRelative(0.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      thresholdSlider.setBoundsRelative(0.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
      ratioLabel.setBoundsRelative(1.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      ratioSlider.setBoundsRelative(1.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
      softnessLabel.setBoundsRelative(2.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      softnessSlider.setBoundsRelative(2.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
      colorLabel.setBoundsRelative(3.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      colorSlider.setBoundsRelative(3.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
      qualityLabel.setBoundsRelative(4.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      qualitySlider.setBoundsRelative(4.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
      reducLabel.setBoundsRelative(5.1/nb_elements, 0.05, 0.8/nb_elements, 0.1);
      reducSlider.setBoundsRelative(5.1/nb_elements, 0.2, 0.8/nb_elements, 0.7);
    }
  }
}
