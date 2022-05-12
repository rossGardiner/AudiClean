#ifndef AUDICLEAN_FILTERLMS_H
#define AUDICLEAN_FILTERLMS_H

#include "NoiseFilter.h"
#include "Fir1.h"

/*
* A pipeline component which extends NoiseFilter as an FIR Least-mean-squared Filter
 */
class FirLMS : public NoiseFilter{
public:
    FirLMS(int nrTaps, double lrate);
    double Filter(double dirtySample, double noiseSample) override;
    void RegisterRemoverCallback(SampleCallback* _removerCallBack);
private:
    Fir1* internalLMS;
    SampleCallback* removerCallback = nullptr;
};


#endif //AUDICLEAN_FILTERLMS_H
