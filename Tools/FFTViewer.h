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

      void generate_grid();
      void display_grid();

    private:
      FFTViewerInterface* interface_;
      FFT<double> fft;

      class Component
      {
      public:
        Component(FFT<double>& fft, ::juce::OpenGLContext& openGLContext);

        /// Init GL ids
        void initialize();
        /// Frees GL ids
        void shutdown();
        /// Changes internal size, useful when the parent component is resized
        void setSize(std::size_t newSize);
        /// Displays data
        void display(const std::vector<double>& data, int depth, int sampling_rate, bool process, GLuint positionID);

      private:
        FFT<double>& fft;
        ::juce::OpenGLContext& openGLContext;
        std::vector<double> amp_data;
        std::vector<double> amp_data_previous;
        std::vector<double> amp_data_log;

        std::vector<float> display_data;
        std::vector<float> temp_display_data;
        /// Cumulative indices for the display
        std::vector<std::size_t> cumulativeIndices;

        GLuint vertexArrayID;
      };

      std::vector<Component> componentsData;
      
      glm::mat4x4 transformationMatrix;
      GLuint gridArrayID;
      std::vector<float> grid_data;

      std::unique_ptr<::juce::OpenGLShaderProgram::Uniform> MVP;
      std::unique_ptr<::juce::OpenGLShaderProgram> shader;
      std::unique_ptr<::juce::OpenGLShaderProgram::Attribute> position;
    };
  }
}

#endif
