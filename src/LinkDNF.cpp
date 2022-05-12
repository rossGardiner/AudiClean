#include "LinkDNF.h"

#define NLAYERS 6

/*!
 * Initialise the DNF, requires nr taps, learning rate and audio samplerate. Learning rate is set for weights only, not biases.
 * @param nrTaps
 * @param lrate
 * @param sampleRate
 */
LinkDNF::LinkDNF(int nrTaps, double lrate, int sampleRate){
    internal_DNF = new DNF(NLAYERS, nrTaps, 1.0 * sampleRate);
    internal_DNF->getNet().setLearningRate(lrate, 0);
}
/*!
 * Takes a dirty signal sample and a noise sample, returns filtered sample. If remover and weight callbacks are registered, pass data from DNF internals
 * @param dirtySample
 * @param noiseSample
 * @return
 */
double LinkDNF::Filter(double dirtySample, double noiseSample) {
    double cancelled = internal_DNF->filter(dirtySample, noiseSample);
    if(callback_remover) callback_remover->NextSample(internal_DNF->getRemover());
    if(callback_weights) callback_weights->NextSample(internal_DNF->getNet().getWeightDistance());
    return cancelled;
}

void LinkDNF::RegisterRemoverCallback(SampleCallback *removerCallback) {
    callback_remover = removerCallback;
}

void LinkDNF::RegisterWeightDistCallback(SampleCallback *weightCallback) {
    callback_weights = weightCallback;
}