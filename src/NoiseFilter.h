//
// Created by ross on 30/04/2022.
//

#ifndef AUDICLEAN_NOISEFILTER_H
#define AUDICLEAN_NOISEFILTER_H

#include <thread>
#include <mutex>
#include <condition_variable>

#include "SampleLink.h"
#include "BlockingQueue.h"
#include "BlockingQueue.cpp"

/*!
 * A pipeline element to derive real-time noise removal filters from. Inherits SampleLink. Derived Classes must implement the pure abstract Filter() function.
 * Noise and dirty samples are synchronised by making use of two instances of BlockingQueue. A worker thread loads each samples pair and performs the filtering per-sample.
 */
class NoiseFilter: public SampleLink{
public:
    void RunFilter();
    std::thread * Start();
    void Stop();
    virtual double Filter(double dirtySample, double noiseSample) = 0;
    void NextSignalSample(double sample);
    void NextNoiseSample(double noise);
    void SetOn(bool state);
    bool GetOn();
    
protected:
    BlockingQueue<double> signalSamples;
    BlockingQueue<double> noiseSamples;
    std::thread worker;
    bool isOn = true;
};


#endif //AUDICLEAN_FIRFILTER_H
