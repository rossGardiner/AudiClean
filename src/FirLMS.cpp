#include "FirLMS.h"

/*!
 * Initialise the LMS FIR Filter, requires nrTaps and learning rate
 * @param nrTaps
 * @param lrate
 */
FirLMS::FirLMS(int nrTaps, double lrate){
    internalLMS = new Fir1(nrTaps);
    internalLMS->setLearningRate(lrate);
}

/*!
 * Takes a dirty signal sample and a noise sample, returns filtered sample
 * @param dirtySample
 * @param noiseSample
 * @return
 */
double FirLMS::Filter(double dirtySample, double noiseSample) {
    double canceller = internalLMS->filter(noiseSample);
    if(removerCallback) removerCallback->NextSample(canceller);
    double outputSignal = dirtySample - canceller;
    internalLMS->lms_update(outputSignal);
    return outputSignal;
}

void FirLMS::RegisterRemoverCallback(SampleCallback* _removerCallBack){
    removerCallback = _removerCallBack;
}
