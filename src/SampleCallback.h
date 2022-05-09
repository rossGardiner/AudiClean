#ifndef AUDICLEAN_SAMPLECALLBACK_H
#define AUDICLEAN_SAMPLECALLBACK_H

/*!
 * A simple callback to pass audio samples through the filtering pipeline. Samples are treated as double-precision values in range [-1, 1]. Derived classes must implement the abstract function NextSample()
 */
class SampleCallback{
public:
    virtual void NextSample(double next) = 0;
};


#endif //AUDICLEAN_SAMPLECALLBACK_H
