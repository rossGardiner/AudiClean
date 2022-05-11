#ifndef AUDICLEAN_FIRDNF_H
#define AUDICLEAN_FIRDNF_H

#include "NoiseFilter.h"
#include <boost/circular_buffer.hpp>
#include "dnf.h"

/*!
 * A pipeline component which extends NoiseFilter as an FIR Deep Neuronal Filter
 */
class LinkDNF : public NoiseFilter{
public:
    LinkDNF(int nrTaps, double lrate, int sampleRate);
    double Filter(double dirtySample, double noiseSample) override;
private:
    DNF* internal_DNF;
};


#endif //AUDICLEAN_FIRDNF_H
