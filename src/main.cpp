#include <iostream>

#include "WavReader.h"
#include "FirLMS.h"
#include "FilterInputSignal.h"
#include "FilterInputNoise.h"

int main() {
    
    WavReader sigReader;
    WavReader noiReader;
    
    
    
    FilterInputSignal sigin;
    FilterInputNoise noisein;
    FirLMS filt(50, 0.001);
    
    sigReader.RegisterCallback(&sigin);
    noiReader.RegisterCallback(&noiReader);
    sigin.RegisterCallback(&filt);
    noisein.RegisterCallback(&filt);
    
    SampleLink endpoint;
    filt.RegisterCallback(&endpoint);
    filt.Start();
    
    sigReader.Start("/home/ross/CLionProjects/AudiClean/wav-files/2harmonic441Hz.wav");
    noiReader.Start("/home/ross/CLionProjects/AudiClean/wav-files/sinewave882Hz.wav");
    
    
    filt.Stop();
    sigReader.Stop();
    noiReader.Stop();
    return 0;
    
}
