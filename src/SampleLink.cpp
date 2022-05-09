#include "SampleLink.h"
/*!
 * Register the callback for the next object in the pipeline.
 * @param scb
 */
void SampleLink::RegisterCallback(SampleCallback *scb) {
    sampleCallback = scb;
}

/*!
 * Default implementation of NextSample. Pass the sample to the next callback, return if no callback is set yet.
 * @param sample
 */
void SampleLink::NextSample(double sample) {
    if(!sampleCallback) return;
    sampleCallback->NextSample(sample);
}