#include "SoxEndpoint.h"

#include <string>

bool SoxEndpoint::Open(int srate, int nchan, std::string globalopts, std::string fileopts, std::string filename, std::string effectopts) {
    std::string cmd("sox " + globalopts + "-t f8 -c " + std::to_string(nchan) + " -r " + std::to_string(srate) + " - " + fileopts + "'" + filename + "' " + effectopts);
    pipe = popen(cmd.c_str(), "r");
    return (pipe != nullptr);
}

void SoxEndpoint::NextSample(double s) {
    fwrite(&s, sizeof(double), 1, pipe);
}

void SoxEndpoint::Close(void) {
    pclose(pipe);
}

