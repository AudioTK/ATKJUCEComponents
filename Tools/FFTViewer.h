/**
 * \file FFTViewer.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_FFTVIEWER
#define ATKJUCECOMPONENTS_TOOLS_FFTVIEWER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_opengl/juce_opengl.h>

#include <ATK/Tools/DryWetFilter.h>

namespace ATK
{
  namespace juce
  {
    class FFTViewerComponent  : public ::juce::OpenGLAppComponent, public ::juce::Timer
    {
    public:
      FFTViewerComponent();
      ~FFTViewerComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void render() override;
    
      void initialise() override;
      void shutdown() override;
      
      void timerCallback() override;
      
    protected:
      
    private:
    };
  }
}

#endif
