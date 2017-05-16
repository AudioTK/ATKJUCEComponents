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
      virtual unsigned int get_slice_size() const = 0;
      virtual const std::vector<double>& get_last_slice(bool& process) = 0;
      
    };
  }
}

#endif
