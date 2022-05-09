#ifndef AUDICLEAN_FILTERLMS_H
#define AUDICLEAN_FILTERLMS_H

#include "FirFilter.h"
#include <Fir1.h>


class FirLMS : public FirFilter{
public:
    FirLMS(int nrTaps, double lrate);
    double Filter(double dirtySample, double noiseSample) override;
private:
    Fir1* internalLMS;
};


#endif //AUDICLEAN_FILTERLMS_H
