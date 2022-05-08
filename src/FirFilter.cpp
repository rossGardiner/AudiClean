#include "FirFilter.h"

FirFilter::FirFilter(int nrTaps, double lrate) {
    nrTaps = nrTaps;
    lrate = lrate;
}

void FirFilter::RunFilter() {
    while(isOn){
        double noiseSample = noiseSamples.Pop();
        double signalSample = signalSamples.Pop();
        double filtered = Filter(signalSample, noiseSample);
        if(sampleCallback) {
            sampleCallback->NextSample(filtered);
        }
    }
}

std::thread * FirFilter::Start() {
    worker = std::thread(&FirFilter::RunFilter, this);
    return &worker;
}

void FirFilter::Stop(){
    //set isOn to false
    isOn = false;
    //add dummy samples to exit run loop
    noiseSamples.Push(0.0);
    signalSamples.Push(0.0);
    //join thread
    worker.join();
}

bool FirFilter::GetOn() {
    return isOn;
}

void FirFilter::SetOn(bool state) {
    isOn = state;
}

void FirFilter::NextSignalSample(double sample){
    signalSamples.Push(sample);
}

void FirFilter::NextNoiseSample(double noise){
    noiseSamples.Push(noise);
}

