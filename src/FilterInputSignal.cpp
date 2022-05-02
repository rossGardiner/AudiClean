//
// Created by ross on 02/05/2022.
//

#include "FilterInputSignal.h"

void FilterInputSignal::RegisterCallback(FirFilter* filterCallback){
    filterCallback = filterCallback;
}

void FilterInputSignal::NextSample(double sample){
    if(!filterCallback) return;
    filterCallback->NextSignalSample(sample);
}