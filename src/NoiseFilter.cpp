#include "NoiseFilter.h"


void NoiseFilter::RunFilter() {
    while(isOn){
        double signalSample = signalSamples.Pop();
        double noiseSample = noiseSamples.Pop();
        double filtered = Filter(signalSample, noiseSample);
        if(sampleCallback) {
            sampleCallback->NextSample(filtered);
        }
    }
}

std::thread * NoiseFilter::Start() {
    worker = std::thread(&NoiseFilter::RunFilter, this);
    return &worker;
}

void NoiseFilter::Stop(){
    isOn = false;
    //add dummy samples to exit run loop
    if(signalSamples.Size() == 0) signalSamples.Push(0.0);
    if(noiseSamples.Size() == 0) noiseSamples.Push(0.0);
    worker.join();
}

bool NoiseFilter::GetOn() {
    return isOn;
}

void NoiseFilter::SetOn(bool state) {
    isOn = state;
}

void NoiseFilter::NextSignalSample(double sample){
    signalSamples.Push(sample);
}

void NoiseFilter::NextNoiseSample(double noise){
    noiseSamples.Push(noise);
}

