#include "SampleLink.h"

void SampleLink::RegisterCallback(SampleCallback *scb) {
    sampleCallback = scb;
}
void SampleLink::NextSample(double sample) {
    if(!sampleCallback) return;
    sampleCallback->NextSample(sample);
}