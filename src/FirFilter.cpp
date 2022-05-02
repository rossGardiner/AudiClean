#include "FirFilter.h"
#include "BlockingQueue.cpp"

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

void FirFilter::Start() {
    worker = std::thread(&FirFilter::RunFilter, this);
}

void FirFilter::Stop(){
    isOn = false;
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

