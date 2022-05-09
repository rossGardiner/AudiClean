#include "SoxEndpoint.h"

#include <string>

bool SoxEndpoint::Open(int srate, int nchan, std::string globalopts, std::string fileopts, std::string filename, std::string effectopts) {
    std::string cmd("sox " + globalopts + "-t f64 -c " + std::to_string(nchan) + " -r " + std::to_string(srate) + " - " + fileopts + "'" + filename + "' " + effectopts);
    pipe = popen(cmd.c_str(), "w");
    return (pipe != nullptr);
}

void SoxEndpoint::NextSample(double s) {
    fwrite(&s, sizeof(double), 1, pipe);
}

void SoxEndpoint::Close(void) {
    if(pipe != nullptr) {
        pclose(pipe);
    }
    
}

