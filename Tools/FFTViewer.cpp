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
      auto ratio = static_cast<float>(getWidth()) / getHeight();
      MVP = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f) *  glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
    
    void FFTViewerComponent::render()
    {
      const float desktopScale = (float) openGLContext.getRenderingScale();
      ::juce::OpenGLHelpers::clear(getLookAndFeel().findColour(::juce::ResizableWindow::backgroundColourId));

      glViewport (0, 0, ::juce::roundToInt (desktopScale * getWidth()), ::juce::roundToInt (desktopScale * getHeight()));
      
      glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
      auto ratio = static_cast<float>(getWidth()) / getHeight();
      
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
          
          auto first_index = std::lround(20. * slice_size / sampling_rate); //Only display between 20 and 20kHz
          auto last_index = std::lround(20000. * slice_size / sampling_rate);
          display_data.resize((last_index - first_index + 1) * 3);
          
          for(auto i = first_index; i <= last_index; ++i)
          {
            auto local_id = i - first_index;
            display_data[local_id * 3] = ratio * (2 * i / (last_index - first_index - 1.f) - 1);
            display_data[local_id * 3 + 1] = (2 * (amp_data_log[index][i] - min_value) / (max_value - min_value + 1e-10) - 1);
            display_data[local_id * 3 + 2] = index;
          }
        }
        
        if(amp_data_log[index].empty())
          return;
        
        openGLContext.extensions.glBufferData (GL_ARRAY_BUFFER,
                                               static_cast<GLsizeiptr> (static_cast<size_t> (display_data.size()) * sizeof (float)),
                                               display_data.data(), GL_STATIC_DRAW);
        openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexArrayID);
        
        openGLContext.extensions.glVertexAttribPointer (position->attributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
        openGLContext.extensions.glEnableVertexAttribArray (position->attributeID);
        
        glDrawElements (GL_LINE_SMOOTH, display_data.size() - 1, GL_UNSIGNED_INT, 0);
        
        shader->use();
        
        openGLContext.extensions.glDisableVertexAttribArray (position->attributeID);
      }
      openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, 0);
    }
    
    void FFTViewerComponent::initialise()
    {
      buildShaders();
    }

    void FFTViewerComponent::shutdown()
    {
      openGLContext.extensions.glDeleteBuffers (1, &vertexArrayID);
    }
    
    void FFTViewerComponent::buildShaders()
    {
      std::string vertexShader =
      "#version 120\n"
      "attribute vec3 position;\n"
      "\n"
      "uniform mat4 MVP;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    vec4 pos;\n"
      "    pos.xyz = position;\n"
      "    pos.w = 1;\n"
      "    gl_Position = MVP * pos;\n"
      "}\n";
      
      std::string fragmentShader =
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
      
      matrixID = glGetUniformLocation(shader->getProgramID(), "MVP");
      position.reset(new ::juce::OpenGLShaderProgram::Attribute(*shader, "position"));
      
      openGLContext.extensions.glGenBuffers (1, &vertexArrayID);
      openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexArrayID);
      
      //glGenVertexArrays(1, &vertexArrayID);
      //glBindVertexArray(vertexArrayID);
    }
  }
}
