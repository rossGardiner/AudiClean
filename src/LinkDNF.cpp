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
 * Takes a dirty signal sample and a noise sample, returns filtered sample
 * @param dirtySample
 * @param noiseSample
 * @return
 */
double LinkDNF::Filter(double dirtySample, double noiseSample) {
    double cancelled = internal_DNF->filter(dirtySample, noiseSample);
    return cancelled;
}