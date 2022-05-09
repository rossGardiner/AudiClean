#ifndef AUDICLEAN_FIRDNF_H
#define AUDICLEAN_FIRDNF_H

#include "FirFilter.h"
#include <boost/circular_buffer.hpp>
#include "dnf.h"


class FirDNF : public FirFilter{
public:
    FirDNF(int nrTaps, double lrate, int sampleRate);
    double Filter(double dirtySample, double noiseSample) override;
private:
    DNF* internal_DNF;
};


#endif //AUDICLEAN_FIRDNF_H
