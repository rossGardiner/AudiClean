#include "SoxEndpoint.h"

#include <string>

bool SoxEndpoint::Open(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename, std::string effectopts) {
    std::string cmd("sox " + globalopts + "-t f8 -c " + std::to_string(nchan) + "- " + fileopts + "'" + filename + "' " + effectopts);
    pipe = popen(cmd.c_str(), "r");
    return (pipe != nullptr);
}

void SoxEndpoint::NextSample(double s) {
    fwrite(&s, sizeof(double), 1, pipe);
}

void SoxEndpoint::Close(void) {
    pclose(pipe);
}

