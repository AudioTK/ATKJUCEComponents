/**
 * \file FFTViewer.cpp
 */

#ifdef WIN32
  #include <windows.h>
#endif
#include <gl/gl.h>

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

      startTimer (200);  // redraw every 200ms
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
      
      glLineWidth(10);
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(-1, -.5, 0);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(1, -.5, 0);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(0, .5, 0);
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
