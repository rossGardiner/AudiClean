#ifndef SOXENDPOINT_H
#define SOXENDPOINT_H

#include "SampleCallback.h"
#include <cstdio>
#include <string>

class SoxEndpoint : public SampleCallback {
public:
    bool Open(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename, std::string effectopts);
    void NextSample(double s);
    void Close(void);
private:
    FILE* pipe;
};

#endif

