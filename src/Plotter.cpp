#include "Plotter.h"
#include <stdlib.h>

void Plotter::NextSample(double next){
    cb->push_back(next);
    std::vector<double> v(cb->begin(), cb->end());
    int f = 0; int s = 0; int t = 0; int l = 0;
    cvui::sparkline(frame, v, f, s ,w, h);
    if(sampleCallback) sampleCallback->NextSample(next);
}

Plotter::Plotter(cv::Mat &_ref, int _bsize, int _w, int _h){
    frame = _ref;
    w = _w;
    h = _h;
    cb = new boost::circular_buffer<double>(_bsize);
}

