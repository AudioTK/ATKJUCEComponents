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

namespace
{
  const double min_value = -380;
  const double max_value = 20;
}

namespace ATK
{
  namespace juce
  {
    FFTViewerComponent::FFTViewerComponent (FFTViewerInterface* interface_)
    :interface_(interface_)
    {
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (400, 300);

      startTimer(100);  // redraw every 100ms
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
      bool process = true;
      const auto& data = interface_->get_last_slice(process);
      double memory_rate = std::exp(-0.3 * data.size() / interface_->get_sampling_rate()); // 300ms release time

      if(process && data.size() > 0)
      {
        fft.set_size(data.size());
        fft.process(data.data(), data.size());
        fft.get_amp(amp_data);
        if(amp_data_previous.size() != amp_data.size())
        {
          amp_data_previous = amp_data;
          amp_data_log.resize(amp_data_previous.size());
        }
        for(std::size_t i = 0; i < amp_data.size(); ++i)
        {
          amp_data_previous[i] = std::max(amp_data[i], memory_rate * amp_data_previous[i]);
          amp_data_log[i] = 20 * std::log(amp_data_previous[i]);
        }
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
      for(std::size_t i = 0; i < amp_data_log.size(); ++i)
      {
        glVertex3f(2 * i / (amp_data_log.size() - 1.f) - 1, 2 * (amp_data_log[i] - min_value) / (max_value - min_value + 1e-10) - 1, 0);
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
