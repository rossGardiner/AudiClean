#ifndef AUDICLEAN_FILTERINPUTSIGNAL_H
#define AUDICLEAN_FILTERINPUTSIGNAL_H

#include "SampleCallback.h"
#include "NoiseFilter.h"

class FilterInputSignal : public SampleCallback{
public:
    void RegisterCallback(NoiseFilter* filterCallback);
    void NextSample(double sample);
protected:
    NoiseFilter* filterCallback;
};


#endif //AUDICLEAN_FILTERINPUTSIGNAL_H
