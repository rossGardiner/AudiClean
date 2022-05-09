#ifndef AUDICLEAN_FILTERINPUTNOISE_H
#define AUDICLEAN_FILTERINPUTNOISE_H

#include "SampleCallback.h"
#include "NoiseFilter.h"

/*!
 * Inherits SampleCallback, acts as an interface to the asynchonous noise input to a NoiseFiler
 */
class FilterInputNoise : public SampleCallback{
public:
    void RegisterCallback(NoiseFilter* filterCallback);
    void NextSample(double sample);
protected:
    NoiseFilter* filterCallback;
};


#endif //AUDICLEAN_FILTERINPUTNOISE_H
