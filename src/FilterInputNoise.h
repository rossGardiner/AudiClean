//
// Created by ross on 02/05/2022.
//

#ifndef AUDICLEAN_FILTERINPUTNOISE_H
#define AUDICLEAN_FILTERINPUTNOISE_H

#include "SampleCallback.h"
#include "FirFilter.h"

class FilterInputNoise : public SampleCallback{
public:
    void RegisterCallback(FirFilter* filterCallback);
    void NextSample(double sample);
protected:
    FirFilter* filterCallback;
};


#endif //AUDICLEAN_FILTERINPUTNOISE_H
