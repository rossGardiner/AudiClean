#include "WavReader.h"

#include <string>
#include <sstream>



void WavReader::Start(std::string filename){
    Open(filename);
    workerThread = std::thread(&WavReader::Run, this);
}

bool WavReader::Open(std::string filename) {
    std::string cmd_sr("soxi -r " + filename);
    pipe = popen(cmd_sr.c_str(), "r");
    if (pipe == nullptr){
        return false;
    }
    fgets(rdbuf, bufmax, pipe);
    std::stringstream sr(rdbuf);
    sr >> sampleRate;
    std::string cmd_cn("soxi -c " + filename);
    pipe = popen(cmd_cn.c_str(), "r");
    if (pipe == nullptr){
        return false;
    }
    fgets(rdbuf, bufmax, pipe);
    std::stringstream cn(rdbuf);
    cn >> nrChannels;
    std::string cmd("sox '" + filename + "' -t dat -c " + std::to_string(nrChannels) + " -");
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
