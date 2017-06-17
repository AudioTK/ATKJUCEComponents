/**
 * \file FFTViewer.cpp
 */

#include <glm/gtc/matrix_transform.hpp>

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
      projectionMatrix = glm::ortho(0.0f, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 0.0f, 0.1f, 100.0f);
      viewMatrix = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
    
    void FFTViewerComponent::render()
    {
      const float desktopScale = (float) openGLContext.getRenderingScale();
      ::juce::OpenGLHelpers::clear (getLookAndFeel().findColour (::juce::ResizableWindow::backgroundColourId));

      glEnable (GL_BLEND);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      auto ratio = static_cast<float>(getWidth()) / getHeight();
      glViewport (0, 0, ::juce::roundToInt (desktopScale * getWidth()), ::juce::roundToInt (desktopScale * getHeight()));
      
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
        
        /*glBegin(GL_LINES);
        glColor4f(colors[3*index], colors[3*index+1], colors[3*index+2], 0.5);
        for(std::size_t i = first_index; i < last_index; ++i)
        {
          glVertex3f(ratio * (2 * i / (last_index - first_index - 1.f) - 1), (2 * (amp_data_log[index][i] - min_value) / (max_value - min_value + 1e-10) - 1), 0);
        }
        glEnd();*/
      }
    }
    
    void FFTViewerComponent::initialise()
    {
      buildShaders();
    }

    void FFTViewerComponent::shutdown()
    {
    }
    
    void FFTViewerComponent::buildShaders()
    {
      std::string vertexShader =
      "attribute vec4 position;\n"
      "attribute vec4 sourceColour;\n"
      "attribute vec2 texureCoordIn;\n"
      "\n"
      "uniform mat4 projectionMatrix;\n"
      "uniform mat4 viewMatrix;\n"
      "\n"
      "varying vec4 destinationColour;\n"
      "varying vec2 textureCoordOut;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    destinationColour = sourceColour;\n"
      "    textureCoordOut = texureCoordIn;\n"
      "    gl_Position = projectionMatrix * viewMatrix * position;\n"
      "}\n";
      
      std::string fragmentShader =
      "varying vec4 destinationColour;\n"
      "varying vec2 textureCoordOut;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    vec4 colour = vec4(0.95, 0.57, 0.03, 0.7);\n"
      "    gl_FragColor = colour;\n"
      "}\n";
      
      std::unique_ptr<::juce::OpenGLShaderProgram> newShader(new ::juce::OpenGLShaderProgram (openGLContext));
      ::juce::String statusText;
      
      if (newShader->addVertexShader(::juce::OpenGLHelpers::translateVertexShaderToV3(vertexShader))
          && newShader->addFragmentShader(::juce::OpenGLHelpers::translateFragmentShaderToV3(fragmentShader))
          && newShader->link())
      {
        shader = std::move(newShader);
        shader->use();
        
        statusText = "GLSL: v" + ::juce::String(::juce::OpenGLShaderProgram::getLanguageVersion(), 2);
      }
      else
      {
        statusText = newShader->getLastError();
      }
    }
  }
}
