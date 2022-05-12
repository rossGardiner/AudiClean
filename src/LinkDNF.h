#ifndef AUDICLEAN_FIRDNF_H
#define AUDICLEAN_FIRDNF_H

#include "NoiseFilter.h"
#include <boost/circular_buffer.hpp>
#include "dnf.h"

/*!
 * A pipeline component which extends NoiseFilter as a Deep Neuronal Filter. Inner workings described by Porr et al : https://arxiv.org/abs/2011.03466
 */
class LinkDNF : public NoiseFilter{
public:
    LinkDNF(int nrTaps, double lrate, int sampleRate);
    double Filter(double dirtySample, double noiseSample) override;
    void RegisterRemoverCallback(SampleCallback* removerCallback);
    void RegisterWeightDistCallback(SampleCallback* weightCallback);
private:
    DNF* internal_DNF;
    SampleCallback* callback_remover = nullptr;
    SampleCallback* callback_weights = nullptr;
};


#endif //AUDICLEAN_FIRDNF_H
