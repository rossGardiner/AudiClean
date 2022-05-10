#ifndef AUDICLEAN_CORRELATOR_H
#define AUDICLEAN_CORRELATOR_H

#include "NoiseFilter.h"

class Correlator : public NoiseFilter {
public:
    double Filter(double dirtySample, double noiseSample) override;
    double GetMean1();
    double GetMean2();
    double GetStdDev1();
    double GetStdDev2();
    double GetCov();
    double GetRho();
    double GetSNR();
private:
    int count = 0;
    double mean_1 = 0.0;
    double mean_2 = 0.0;
    double stddev_1 = 0.0;
    double stddev_2 = 0.0;
    double cov = 0.0;
    double rho = 0.0;
    double SNR_db = 1.0;
};


#endif //AUDICLEAN_CORRELATOR_H
