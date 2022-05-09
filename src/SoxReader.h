#ifndef AUDICLEAN_WAVREADER_H
#define AUDICLEAN_WAVREADER_H

#include <thread>
#include <stdio.h>

#include "SampleLink.h"

/*!
 * A pipeline element which allows samples to be piped from the SoX program.
 */
class SoxReader : public SampleLink{
public:
    bool Open(int rate, int nchans, std::string globalopts, std::string fileopts, std::string filename);
    std::thread * Start(int rate, int nchans, std::string globalopts, std::string fileopts, std::string filename);
    void ForceStop();
    void Run();
    int GetNumChannels();
    int GetSampleRate();
    void SetOn(bool val);
    
private:
    bool isOn = true;
    int nrChannels = 0;
    int sampleRate = 0;
    void NextSample(float sample);
    FILE* pipe;
    std::thread workerThread;
    static int constexpr bufmax {64};
    char rdbuf[bufmax];
};

extern int get_wav_attr(std::string attr, std::string filename);

#endif //AUDICLEAN_WAVREADER_H
