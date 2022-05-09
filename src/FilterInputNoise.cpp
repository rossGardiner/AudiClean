#include "FilterInputNoise.h"

void FilterInputNoise::RegisterCallback(NoiseFilter* _filterCallback){
    filterCallback = _filterCallback;
}

void FilterInputNoise::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextNoiseSample(sample);
}