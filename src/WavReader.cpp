#include "WavReader.h"

#include <string>
#include <sstream>



std::thread * WavReader::Start(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename){
    if(!Open(rate, nchan, globalopts, fileopts, filename)) return nullptr;
    workerThread = std::thread(&WavReader::Run, this);
    return &workerThread;
}

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

bool WavReader::Open(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename) {
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

void WavReader::SetOn(bool val) {
    isOn = val;
}

void WavReader::Run() {
    bool eof = false;
    while(isOn && !eof){
        eof = (fgets(rdbuf, bufmax, pipe) == nullptr);
        std::stringstream ss(rdbuf);
        double t, s;
        printf("%s\n", ss.str().c_str());
        ss >> t >> s;
        sampleCallback->NextSample(s);
    }
}

void WavReader::Stop(){
    SetOn(false);
    if(pipe != nullptr){
        pclose(pipe);
    }
    workerThread.join();
}

int WavReader::GetNumChannels() {
    return nrChannels;
}

int WavReader::GetSampleRate() {
    return sampleRate;
}
