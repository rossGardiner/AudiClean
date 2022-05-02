//
// Created by ross on 02/05/2022.
//

#include "FilterInputNoise.h"

void FilterInputNoise::RegisterCallback(FirFilter* filterCallback){
    filterCallback = filterCallback;
}

void FilterInputNoise::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextNoiseSample(sample);
}