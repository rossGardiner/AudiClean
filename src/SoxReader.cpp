#include "SoxReader.h"

#include <string>
#include <sstream>


/*!
 * Starts reading from the pipe from SoX, returns a thread which lives as long as the pipe does
 * @param rate
 * @param nchan
 * @param globalopts
 * @param fileopts
 * @param filename
 * @return
 */
std::thread * SoxReader::Start(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename){
    if(!Open(rate, nchan, globalopts, fileopts, filename)) return nullptr;
    workerThread = std::thread(&SoxReader::Run, this);
    return &workerThread;
}
/*!
 * Gets attributes from the audio file to be opened with sox.
 * @param attr
 * @param filename
 * @return
 */
int get_wav_attr(std::string attr, std::string filename) {
    FILE* pipe;
    static int constexpr bufmax {64};
    char rdbuf[bufmax];
    int ret;
    std::string cmd_sr("soxi -" + attr + " " + filename);
    pipe = popen(cmd_sr.c_str(), "r");
    if (pipe == nullptr){
        return 0;
    }
    fgets(rdbuf, bufmax, pipe);
    std::stringstream str(rdbuf);
    str >> ret;
    return ret;
}

/*!
 * Open the pipe from SoX
 * @param rate
 * @param nchan
 * @param globalopts
 * @param fileopts
 * @param filename
 * @return true if opening file successful, false otherwise.
 */
bool SoxReader::Open(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename) {
    sampleRate = rate ?: get_wav_attr("r", filename);
    nrChannels = nchan ?: get_wav_attr("c", filename);
    if(!sampleRate || !nrChannels) return false;
    std::string cmd("sox " + globalopts + fileopts + "'" + filename + "' -t dat -c " + std::to_string(nrChannels) + " -");
    pipe = popen(cmd.c_str(), "r");
    if (pipe == nullptr){
        return false; //file failed to open
    }
    return true;
}

/*!
 * Sets the isOn status of the SoxReader
 * @param val
 */
void SoxReader::SetOn(bool val) {
    isOn = val;
}

/*!
 * Work function for the worker thread, reads samples from the SoX pipe, processes them and passes on to the next pipeline element. Continues while isOn is set and the end of the pipe is not reached.
 */
void SoxReader::Run() {
    bool eof = false;
    eof = (fgets(rdbuf, bufmax, pipe) == nullptr);
    eof = (fgets(rdbuf, bufmax, pipe) == nullptr);
    while(isOn && !eof){
        eof = (fgets(rdbuf, bufmax, pipe) == nullptr);
        std::stringstream ss(rdbuf);
        double t, s;
        ss >> t >> s;
        sampleCallback->NextSample(s);
    }
    if(pipe!= nullptr){
        pclose(pipe);
    }
}
/*!
 * Brute-force stop the SoxReader, will attempt to close the pipe and join the worker thread.
 */
void SoxReader::ForceStop(){
    SetOn(false);
    if(pipe != nullptr){
        pclose(pipe);
    }
    workerThread.join();
}
/*!
 * Gets the nr of channels in the audio file to open
 * @return
 */
int SoxReader::GetNumChannels() {
    return nrChannels;
}
/*!
 * Gets the sample rate of the audio file to open
 * @return
 */
int SoxReader::GetSampleRate() {
    return sampleRate;
}
