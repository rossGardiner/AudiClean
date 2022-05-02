#ifndef AUDICLEAN_SAMPLECALLBACK_H
#define AUDICLEAN_SAMPLECALLBACK_H

class SampleCallback{
public:
    virtual void NextSample(double next) = 0;
};


#endif //AUDICLEAN_SAMPLECALLBACK_H
