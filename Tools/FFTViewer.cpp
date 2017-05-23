/**
 * \file FFTViewer.cpp
 */

#ifdef WIN32
  #include <windows.h>
  #include <gl/gl.h>
#else
  #include <OpenGL/gl.h>
#endif

#include <array>

#include "FFTViewer.h"
#include "FFTViewerInterface.h"

namespace
{
  const double min_value = -200;
  const double max_value = 0;
  
  const std::array<float, 6> colors{{0, 1, 0, 1, 0, 0}};
}

namespace ATK
{
  namespace juce
  {
    FFTViewerComponent::FFTViewerComponent (FFTViewerInterface* interface_)
    :interface_(interface_), amp_data(interface_->get_nb_channels()), amp_data_previous(interface_->get_nb_channels()), amp_data_log(interface_->get_nb_channels())
    {
      // Make sure that before the constructor has finished, you've set the
      // editor's size to whatever you need it to be.
      setSize (800, 600);

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
      
      for(std::size_t index = 0; index < amp_data.size(); ++index)
      {
        bool process = true;
        const auto& data = interface_->get_last_slice(index, process);
        auto sampling_rate = interface_->get_sampling_rate();
        auto slice_size = data.size();
        double memory_rate = std::exp(-0.3 * data.size() / sampling_rate); // 300ms release time
        
        if(process && data.size() > 0)
        {
          fft.set_size(slice_size);
          fft.process(data.data(), slice_size);
          fft.get_amp(amp_data[index]);
          if(amp_data_previous[index].size() != amp_data[index].size())
          {
            amp_data_previous[index] = amp_data[index];
            amp_data_log[index].resize(amp_data_previous[index].size());
          }
          for(std::size_t i = 0; i < amp_data[index].size(); ++i)
          {
            amp_data_previous[index][i] = std::max(amp_data[index][i], memory_rate * amp_data_previous[index][i]);
            amp_data_log[index][i] = 10 * std::log(amp_data_previous[index][i]); // amp_data is power
          }
        }
        
        if(amp_data_log[index].empty())
          return;
        
        auto first_index = std::lround(20. * slice_size / sampling_rate); //Only display between 20 and 20kHz
        auto last_index = std::lround(20000. * slice_size / sampling_rate);
        
        glBegin(GL_LINES);
        glColor4f(colors[3*index], colors[3*index+1], colors[3*index+2], 0.5);
        for(std::size_t i = first_index; i < last_index; ++i)
        {
          glVertex3f(ratio * (2 * i / (last_index - first_index - 1.f) - 1), (2 * (amp_data_log[index][i] - min_value) / (max_value - min_value + 1e-10) - 1), 0);
        }
        glEnd();
      }
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
