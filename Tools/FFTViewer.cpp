/**
 * \file FFTViewer.cpp
 */

#ifdef WIN32
  #include <windows.h>
  #include <gl/gl.h>
#else
  #include <OpenGL/gl.h>
#endif

#include "FFTViewer.h"
#include "FFTViewerInterface.h"

namespace ATK
{
  namespace juce
  {
    FFTViewerComponent::FFTViewerComponent (FFTViewerInterface* interface)
    :interface(interface)
    {
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (400, 300);

      startTimer (100);  // redraw every 100ms
    }
    
    FFTViewerComponent::~FFTViewerComponent()
    {
      shutdownOpenGL();
    }
    
    void FFTViewerComponent::paint(::juce::Graphics& g)
    {
      g.setColour (getLookAndFeel().findColour (::juce::Label::textColourId));
      g.setFont (20);
      g.drawText ("OpenGL Example", 25, 20, 300, 30, ::juce::Justification::left);
      g.drawLine (20, 20, 170, 20);
      g.drawLine (20, 50, 170, 50);
    }

    void FFTViewerComponent::resized()
    {
    }
    
    void FFTViewerComponent::render()
    {
      double min = 0;
      double max = 1;
      const auto& data = interface->get_last_slice();

      if(data.size() > 0)
      {
        fft.set_size(data.size());
        fft.process(data.data(), data.size());
        fft.get_amp(amp_data);
        for(auto& data: amp_data)
        {
          data = 20 * std::log(data);
        }
        min = *std::min_element(amp_data.begin(), amp_data.end());
        max = *std::max_element(amp_data.begin(), amp_data.end());
      }
      
      
      const float desktopScale = (float) openGLContext.getRenderingScale();
      ::juce::OpenGLHelpers::clear (getLookAndFeel().findColour (::juce::ResizableWindow::backgroundColourId));

      glEnable(GL_POINT_SMOOTH);
      glEnable (GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      auto ratio = static_cast<float>(getWidth()) / getHeight();
      glViewport (0, 0, ::juce::roundToInt (desktopScale * getWidth()), ::juce::roundToInt (desktopScale * getHeight()));

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-ratio, ratio, -1, 1, 1, -1);
      
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      for(std::size_t i = 0; i < amp_data.size(); ++i)
      {
        glVertex3f(2 * i / (amp_data.size() - 1.f) - 1, 2 * (amp_data[i] - min) / (max - min) - 1, 0);
      }
      
      glEnd();
    }
    
    void FFTViewerComponent::initialise()
    {
    }

    void FFTViewerComponent::shutdown()
    {
    }

    void FFTViewerComponent::timerCallback()
    {
      repaint();
    }
  }
}
