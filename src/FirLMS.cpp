#include "FirLMS.h"

FirLMS::FirLMS(int nrTaps, double lrate) : FirFilter(nrTaps, lrate) {
    internalLMS = new Fir1(nrTaps);
    internalLMS->setLearningRate(lrate);
}

double FirLMS::Filter(double dirtySample, double noiseSample) {
    return 0.0;
}