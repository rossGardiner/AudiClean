//
// Created by ross on 02/05/2022.
//

#include "FilterInputNoise.h"

void FilterInputNoise::RegisterCallback(FirFilter* _filterCallback){
    filterCallback = _filterCallback;
}

void FilterInputNoise::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextNoiseSample(sample);
}