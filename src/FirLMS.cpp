#include "FirLMS.h"

FirLMS::FirLMS(int nrTaps, double lrate) : FirFilter(nrTaps, lrate) {
    internalLMS = new Fir1(nrTaps);
    internalLMS->setLearningRate(lrate);
}

double FirLMS::Filter(double dirtySample, double noiseSample) {
    double canceller = internalLMS->filter(dirtySample);
    double outputSignal = noiseSample - canceller;
    internalLMS->lms_update(outputSignal);
    return outputSignal;
}