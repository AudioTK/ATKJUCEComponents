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

#include <glm/glm.hpp>

namespace ATK
{
  namespace juce
  {
    class FFTViewerInterface;
    class FFTViewerComponent  : public ::juce::OpenGLAppComponent
    {
    public:
      FFTViewerComponent(FFTViewerInterface* interface_);
      ~FFTViewerComponent();
      
      //==============================================================================
      void paint(::juce::Graphics&) override;
      void resized() override;
      void render() override;
    
      void initialise() override;
      void shutdown() override;
    protected:
      
      void buildShaders();
      
    private:
      FFTViewerInterface* interface_;
      FFT<double> fft;

      class Component
      {
      public:
        Component(FFT<double>& fft, ::juce::OpenGLContext& openGLContext);

        void display(const std::vector<double>& data, int index, int sampling_rate, bool process, GLuint vertexArrayID, GLuint positionID);

      private:
        FFT<double>& fft;
        ::juce::OpenGLContext& openGLContext;
        std::vector<double> amp_data;
        std::vector<double> amp_data_previous;
        std::vector<double> amp_data_log;

        std::vector<float> display_data;

      };

      std::vector<Component> componentsData;
      
      glm::mat4x4 transformationMatrix;
      GLuint vertexArrayID;
      
      std::unique_ptr<::juce::OpenGLShaderProgram::Uniform> MVP;
      std::unique_ptr<::juce::OpenGLShaderProgram> shader;
      std::unique_ptr<::juce::OpenGLShaderProgram::Attribute> position;
    };
  }
}

#endif
