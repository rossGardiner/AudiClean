#ifndef AUDICLEAN_SAMPLELINK_H
#define AUDICLEAN_SAMPLELINK_H

#include "SampleCallback.h"
/*!
 * Extends SampleCallback to include facility to register a futher callback. Forms a pipeline element with an input and output.
 */
class SampleLink : public SampleCallback {
public:
   void RegisterCallback(SampleCallback* scb);
   void NextSample(double next);

protected:
        SampleCallback* sampleCallback = nullptr;
};

#endif //AUDICLEAN_SAMPLELINK_H
