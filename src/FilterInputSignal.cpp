//
// Created by ross on 02/05/2022.
//

#include "FilterInputSignal.h"
/*!
 * Registers a NoiseFilter to call-back with signal samples
 * @param _filterCallback
 */
void FilterInputSignal::RegisterCallback(NoiseFilter* _filterCallback){
    filterCallback = _filterCallback;
}
/*!
 * Processes the next signal sample. If a callback is registered, send the sample to the filter signal input
 * @param sample
 */
void FilterInputSignal::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextSignalSample(sample);
}