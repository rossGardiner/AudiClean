#include "FilterInputNoise.h"

/*!
 * Registers a NoiseFilter to call-back with noise samples
 * @param _filterCallback
 */
void FilterInputNoise::RegisterCallback(NoiseFilter* _filterCallback){
    filterCallback = _filterCallback;
}

/*!
 * Processes the next noise sample. If a callback is registered, send the sample to the filter noise input
 * @param sample
 */
void FilterInputNoise::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextNoiseSample(sample);
}