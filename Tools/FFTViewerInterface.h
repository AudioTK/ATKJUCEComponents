/**
 * \file FFTViewerInterface.h
 */

#ifndef ATKJUCECOMPONENTS_TOOLS_FFTVIEWERINTERFACE
#define ATKJUCECOMPONENTS_TOOLS_FFTVIEWERINTERFACE


namespace ATK
{
  namespace juce
  {
    class FFTViewerInterface
    {
    public:
      virtual ~FFTViewerInterface(){}
      
      virtual int get_sampling_rate() const = 0;
      virtual std::size_t get_nb_channels() const = 0;
      virtual const std::vector<double>& get_last_slice(std::size_t index, bool& process) = 0;
      
    };
  }
}

#endif
