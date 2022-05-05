#include "WavReader.h"

#include <string>
#include <sstream>



void WavReader::Start(int rate, int nchan, std::string globalopts, std::string fileopts, std::string filename){
    Open(rate, nchan, globalopts, fileopts, filename);
    workerThread = std::thread(&WavReader::Run, this);
}

static int get_attr(std::string attr, std::string filename) {
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
    sampleRate = rate ?: get_attr("r", filename);
    nrChannels = nchan ?: get_attr("c", filename);
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
    while(isOn){
        eof = (fgets(rdbuf, bufmax, pipe) == nullptr);
        while(!eof && isOn) {
            std::stringstream ss(rdbuf);
            double t, s;
            ss >> t >> s;
            sampleCallback->NextSample(s);
        }
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
