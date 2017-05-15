/**
 * \file FFTViewer.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_FFTVIEWER
#define ATKJUCECOMPONENTS_TOOLS_FFTVIEWER

#include <AppConfig.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_opengl/juce_opengl.h>

#include <ATK/Tools/DryWetFilter.h>
#include <ATK/Utility/FFT.h>

namespace ATK
{
  namespace juce
  {
    class FFTViewerInterface;
    class FFTViewerComponent  : public ::juce::OpenGLAppComponent, public ::juce::Timer
    {
    public:
      FFTViewerComponent(FFTViewerInterface* interface);
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
      FFTViewerInterface* interface;
      FFT<double> fft;
      std::vector<double> amp_data;
    };
  }
}

#endif
