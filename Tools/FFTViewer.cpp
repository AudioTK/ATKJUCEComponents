/**
 * \file FFTViewer.cpp
 */

#include <JuceHeader.h>

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
    :interface_(interface_)
    {
      for (std::size_t i = 0; i < interface_->get_nb_channels(); ++i)
      {
        componentsData.emplace_back(fft, openGLContext);
      }
      openGLContext.setOpenGLVersionRequired(::juce::OpenGLContext::openGL3_2);
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
      auto width = getWidth();
      for (auto& component : componentsData)
      {
        component.setSize(width);
      }

    }
    
    void FFTViewerComponent::render()
    {
      const float desktopScale = (float) openGLContext.getRenderingScale();
      ::juce::OpenGLHelpers::clear(getLookAndFeel().findColour(::juce::ResizableWindow::backgroundColourId));

      glEnable (GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);

      glViewport (0, 0, ::juce::roundToInt (desktopScale * getWidth()), ::juce::roundToInt (desktopScale * getHeight()));
      shader->use();

      MVP->setMatrix4(&transformationMatrix[0][0], 1, GL_FALSE);

      display_grid();

      for(std::size_t index = 0; index < componentsData.size(); ++index)
      {
        bool process = true;
        const auto& data = interface_->get_last_slice(index, process);
        auto sampling_rate = interface_->get_sampling_rate();

        componentsData[index].display(data, index, sampling_rate, process, position->attributeID);
      }

      openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void FFTViewerComponent::initialise()
    {
      buildShaders();
      for (auto& component : componentsData)
      {
        component.initialize();
      }
    }

    void FFTViewerComponent::shutdown()
    {
      openGLContext.extensions.glDeleteBuffers(1, &gridArrayID);
      for (auto& component : componentsData)
      {
        component.shutdown();
      }
    }
    
    void FFTViewerComponent::buildShaders()
    {
      std::string vertexShader =
        "attribute vec3 position;\n"
        "\n"
        "uniform mat4 MVP;\n"
        "\n"
        "void main()\n"
        "{\n"
        "  vec4 pos;\n"
        "  pos.xyz = position;\n"
        "  pos.w = 1;\n"
        "  gl_Position = MVP * pos;\n"
        "}\n";

      std::string fragmentShader =
        "void main()\n"
        "{\n"
        "  gl_FragColor = vec4(1,0,0,1);\n"
        "}";
      
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
      
      transformationMatrix = glm::ortho(-1.f, 1.f, -1.f, 1.f, 10.f, -10.f) *glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
      MVP.reset(new ::juce::OpenGLShaderProgram::Uniform(*shader, "MVP"));
      position.reset(new ::juce::OpenGLShaderProgram::Attribute(*shader, "position"));

      openGLContext.extensions.glGenBuffers(1, &gridArrayID);
      auto nb_10dB = std::lround((max_value - min_value) / 10) + 1;
      grid_data.resize(6 * nb_10dB);

      for (long i = 0; i < nb_10dB; ++i)
      {
        grid_data[6 * i] = -1;
        grid_data[6 * i + 1] = i * 2. / (nb_10dB - 1) - 1;
        grid_data[6 * i + 2] = 10;
        grid_data[6 * i + 3] = 1;
        grid_data[6 * i + 4] = i * 2. / (nb_10dB - 1) - 1;
        grid_data[6 * i + 5] = 10;
      }
    }

    void FFTViewerComponent::display_grid()
    {
      openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, gridArrayID);
      openGLContext.extensions.glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr> (static_cast<size_t> (grid_data.size()) * sizeof(float)), grid_data.data(), GL_STATIC_DRAW);

      openGLContext.extensions.glEnableVertexAttribArray(position->attributeID);
      openGLContext.extensions.glVertexAttribPointer(position->attributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_LINES, 0, grid_data.size() / 3);

      openGLContext.extensions.glDisableVertexAttribArray(position->attributeID);
    }

    FFTViewerComponent::Component::Component(FFT<double>& fft, ::juce::OpenGLContext& openGLContext)
    :fft(fft), openGLContext(openGLContext)
    {
    }

    void FFTViewerComponent::Component::initialize()
    {
      openGLContext.extensions.glGenBuffers(1, &vertexArrayID);
    }

    void FFTViewerComponent::Component::shutdown()
    {
      openGLContext.extensions.glDeleteBuffers(1, &vertexArrayID);
    }

    void FFTViewerComponent::Component::setSize(std::size_t newSize)
    {
      cumulativeIndices.resize(newSize);
    }

    void FFTViewerComponent::Component::display(const std::vector<double>& data, int depth, int sampling_rate, bool process, GLuint positionID)
    {
      auto slice_size = data.size();

      if ((sampling_rate != 0) && process && (data.size() > 0))
      {
        double memory_rate = std::exp(-0.3 * data.size() / sampling_rate); // 300ms release time
        fft.set_size(slice_size);
        fft.process(data.data(), slice_size);
        fft.get_amp(amp_data);
        if (amp_data_previous.size() != amp_data.size())
        {
          amp_data_previous = amp_data;
          amp_data_log.resize(amp_data_previous.size());

          for (std::size_t i = 0; i < cumulativeIndices.size(); ++i)
          {
            cumulativeIndices[i] = std::lround((i + 1) / double(cumulativeIndices.size()) * (20000 - 20) * slice_size / sampling_rate);
          }
        }

        for (std::size_t i = 0; i < amp_data.size(); ++i)
        {
          amp_data_previous[i] = std::max(amp_data[i], memory_rate * amp_data_previous[i]);
          amp_data_log[i] = 10 * std::log(amp_data_previous[i]); // amp_data is power
        }

        auto first_index = std::lround(20. * slice_size / sampling_rate); //Only display between 20 and 20kHz
        auto last_index = std::lround(20000. * slice_size / sampling_rate);
        display_data.resize(cumulativeIndices.size() * 3);

        std::size_t previous_index = 0;
        for (std::size_t local_id = 0; local_id < cumulativeIndices.size(); ++local_id)
        {
          display_data[local_id * 3] = (local_id * 2. / (cumulativeIndices.size() - 1)) - 1;
          display_data[local_id * 3 + 1] = 0;
          display_data[local_id * 3 + 2] = depth;
          for (std::size_t index = previous_index; index < cumulativeIndices[local_id]; ++index)
          {
            display_data[local_id * 3 + 1] += (2 * (amp_data_log[first_index + index] - min_value) / (max_value - min_value + 1e-10) - 1);
          }
          display_data[local_id * 3 + 1] /= cumulativeIndices[local_id] - previous_index;
          previous_index = cumulativeIndices[local_id];
        }
      }

      if (display_data.size() == 0)
        return;

      openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
      openGLContext.extensions.glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr> (static_cast<size_t> (display_data.size()) * sizeof(float)), display_data.data(), GL_STATIC_DRAW);

      openGLContext.extensions.glEnableVertexAttribArray(positionID);
      openGLContext.extensions.glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_LINE_STRIP, 0, (display_data.size() / 3) - 1);

      openGLContext.extensions.glDisableVertexAttribArray(positionID);
    }
  }
}
