/**
 * \file FFTViewer.cpp
 */

#include "FFTViewer.h"

namespace ATK
{
  namespace juce
  {
    FFTViewerComponent::FFTViewerComponent ()
    {
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (400, 300);
    }
    
    FFTViewerComponent::~FFTViewerComponent()
    {
    }
    
    void FFTViewerComponent::paint(::juce::Graphics& g)
    {
      g.fillRoundedRectangle(5, 5, getWidth() - 10, getHeight() - 10, 10);
    }

    void FFTViewerComponent::resized()
    {
    }
    
    void FFTViewerComponent::render()
    {
    }

    void FFTViewerComponent::initialise()
    {
    }

    void FFTViewerComponent::shutdown()
    {
    }
  }
}
