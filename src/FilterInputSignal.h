#ifndef AUDICLEAN_FILTERINPUTSIGNAL_H
#define AUDICLEAN_FILTERINPUTSIGNAL_H

#include "SampleCallback.h"
#include "FirFilter.h"

class FilterInputSignal : public SampleCallback{
public:
    void RegisterCallback(FirFilter* filterCallback);
    void NextSample(double sample);
protected:
    FirFilter* filterCallback;
};


#endif //AUDICLEAN_FILTERINPUTSIGNAL_H
