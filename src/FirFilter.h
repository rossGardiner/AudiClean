//
// Created by ross on 30/04/2022.
//

#ifndef AUDICLEAN_FIRFILTER_H
#define AUDICLEAN_FIRFILTER_H

#include <thread>
#include <mutex>
#include <condition_variable>

#include "SampleLink.h"
#include "BlockingQueue.h"

class FirFilter: public SampleLink{
public:
    FirFilter(int nrTaps, double lrate);
    void RunFilter();
    void Start();
    void Stop();
    virtual double Filter(double dirtySample, double noiseSample) = 0;
    void NextSignalSample(double sample);
    void NextNoiseSample(double noise);
    void SetOn(bool state);
    bool GetOn();
    
    
protected:
    BlockingQueue<double> signalSamples;
    BlockingQueue<double> noiseSamples;
    double lrate = 0.0;
    int nrTaps = 0;
    std::thread worker;
    bool isOn = true;
};


#endif //AUDICLEAN_FIRFILTER_H
