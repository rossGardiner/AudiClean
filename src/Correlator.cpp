#include "Correlator.h"

double Correlator::Filter(double dirtySample, double noiseSample){
    mean_1 = (mean_1 + dirtySample) / (1.0 * count);
    mean_2 = (mean_2 + noiseSample) / (1.0 * count);
    
}
double Correlator::GetMean1() {
    return mean_1;
}
double Correlator::GetMean2() {
    return mean_2;
}
double Correlator::GetStdDev1(){
    return stddev_1;
}
double Correlator::GetStdDev2(){
    return stddev_2;
}
double Correlator::GetCov(){
    return cov;
}
double Correlator::GetRho(){
    return rho;
}
double Correlator::GetSNR(){
    return SNR_db;
}