#include <iostream>

#include "WavReader.h"
#include "FirLMS.h"
#include "FilterInputSignal.h"
#include "FilterInputNoise.h"

int main() {
    
    //WavReader sigReader;
    //WavReader noiReader;
    
    
    
    FilterInputSignal sigin;
    FilterInputNoise noisein;
    FirLMS filt(50, 0.001);
    //sigin.RegisterCallback(&filt);
    //noisein.RegisterCallback(&filt);
    
    SampleLink endpoint;
    filt.RegisterCallback(&endpoint);
    //sigReader.Start("/home/ross/CLionProjects/AudiClean/wav-files/2harmonic441Hz.wav");
    //noiReader.Start("/home/ross/CLionProjects/AudiClean/wav-files/sinewave882Hz.wav");
    filt.Start();
    
    std::cout << "Hello, World!" << std::endl;
    
    //sigReader.Stop();
    //noiReader.Stop();
    filt.Stop();
    return 0;
    
}
