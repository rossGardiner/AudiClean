#include "SoxEndpoint.h"

#include <string>
/*!
 * Open the SoX pipe
 * @param srate sample rate for pipe
 * @param nchan nr of channels in filtered audio
 * @param globalopts
 * @param fileopts
 * @param filename filename to pass to sox
 * @param effectopts options for SoX effects
 * @return true if open sucessful, false otherwise
 */
bool SoxEndpoint::Open(int srate, int nchan, std::string globalopts, std::string fileopts, std::string filename, std::string effectopts) {
    std::string cmd("sox " + globalopts + "-t f64 -c " + std::to_string(nchan) + " -r " + std::to_string(srate) + " - " + fileopts + "'" + filename + "' " + effectopts);
    pipe = popen(cmd.c_str(), "w");
    return (pipe != nullptr);
}

/*!
 * Adds the next sample to the output pipe
 * @param s
 */
void SoxEndpoint::NextSample(double s) {
    fwrite(&s, sizeof(double), 1, pipe);
}

/*!
 * Close the output pipe if it exists
 */
void SoxEndpoint::Close(void) {
    if(pipe != nullptr) {
        pclose(pipe);
    }
    
}

